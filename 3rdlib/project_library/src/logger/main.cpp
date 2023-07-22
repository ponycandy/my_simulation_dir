// For Windows, include <winsock2.h> and <ws2tcpip.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cstring>
#include <queue>
#include <vector>
#include <sstream>
#include "spdlog/sinks/rotating_file_sink.h"
#include <libxl.h>
#define headerlength 6
using namespace libxl;
// For Windows, initialize the Winsock library
// Frame header structure
#pragma pack(push,1)
struct Header
{
    short sequence;
    short Id;
    short length;
    char* data;
};
#pragma pack(pop)


class  mylogger
{
public:
    mylogger();
    ~mylogger();

    std::shared_ptr<spdlog::logger> m_logger;
    std::shared_ptr<spdlog::logger> console;
    libxl::Book* m_book;
    Sheet* sheet;
    std::string xlsfilename;

    void processPacket(Header* unpackedHeader);
};

mylogger::mylogger()
{
}

mylogger::~mylogger()
{
}
int findSequenceIndex(const char* arr, int size)
{
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == '\xaa' && arr[i + 1] == '\xaa') {
            return i;
        }
    }

    return -1; // Return -1 if the sequence is not found
}
// Function to extract the message from a single packet
void seperateTriplet(int& row, int& col, double& value, std::string input)
{
    std::stringstream ss(input);
    double number;
    int i = 0;
    while (ss >> number) { // Extracting numbers directly from stringstream
        //std::cout << "Number: " << number << std::endl;
        if (i == 0)
        {
            row = number;
            i++;
            continue;
        }
        if (i == 1)
        {
            col = number;
            i++;
            continue;
        }
        if (i == 2)
        {
            value = number;
            i++;
            continue;
        }
    }

    return;
}
std::string extractMessage(const char& packet) {
    // Extract the header from the packet
    Header frameHeader;
    std::memcpy(&frameHeader, (void*)&packet, sizeof(Header));

    // Extract the message from the packet based on the length in the frame header
    std::string message(&packet, sizeof(Header), frameHeader.length);

    return message;
}
void mylogger::processPacket(Header* unpackedHeader)
{
    short A_ID = 0xaabb;
    if (unpackedHeader->Id == A_ID)
    {
        //log至文本
        std::string message(unpackedHeader->data, unpackedHeader->length);
        m_logger->info(message);
        m_logger->flush();
        return;
    }
    A_ID = 0xaacc;
    if (unpackedHeader->Id == A_ID)
    {
        //打印输入
        std::string message(unpackedHeader->data, unpackedHeader->length);
        std::cout << message << std::endl;
        return;
    }
    A_ID = 0xaadd;
    if (unpackedHeader->Id == A_ID)
    {
        //打印输入,并且录入文件
        std::string message(unpackedHeader->data, unpackedHeader->length);
        console->info(message);
        m_logger->info(message);
        m_logger->flush();
        return;
    }
    A_ID = 0xaaee;
    if (unpackedHeader->Id == A_ID)
    {
        std::string message(unpackedHeader->data, unpackedHeader->length);

        xlsfilename = message;
        //根据文件名message创建表格文件
        if (m_book->load(message.c_str()))
        {
            // Existing XLS file has been opened
            int a = 1;
        }
        else 
        {
            int a = 1;
            // New XLS file has been created
        }
        sheet = m_book->addSheet("Sheet1");  // Create a new sheet (if not exist)
        return;
    }
    A_ID = 0xaaff;
    if (unpackedHeader->Id == A_ID)
    {
        //写入上面的表格文件
        int row,col;
        double value;
        std::string message(unpackedHeader->data, unpackedHeader->length);
        seperateTriplet(row, col, value, message);
        sheet->writeNum(row, col, value);        
        return;
    }
    A_ID = 0xbbaa;
    if (unpackedHeader->Id == A_ID)
    {
        //保存表格文件

        m_book->save(xlsfilename.c_str());
        m_book->release();
        return;
    }
    return;
}
std::string crop_string(const std::string& input, const std::string& delimiter) {
    std::size_t pos = input.find(delimiter); // Find the position of the delimiter

    if (pos == std::string::npos) { // Delimiter not found
        return input;
    }

    return input.substr(pos + delimiter.length()); // Crop out the substring after the delimiter
}
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <integer> <string>" << std::endl;
        return 1;
    }
    mylogger* m_logger = new mylogger;
    int portnum = std::stoi(argv[1]);
    std::string filename = argv[2];
    m_logger->m_logger = spdlog::basic_logger_mt("basic_logger", filename);
    //m_logger->m_logger = spdlog::rotating_logger_mt("basic_logger", filename);
    m_logger->console = spdlog::stdout_color_mt("console");
    m_logger->m_book = xlCreateBook();
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return -1;
    }

    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        WSACleanup();
        return -1;
    }

    // Bind the socket to a local address and port
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portnum); // Convert from host byte order to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY; // Listen on any local address
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket\n";
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Failed to listen on socket\n";
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Accept a connection from a client
    sockaddr_in client_address;
    int client_size = sizeof(client_address);
    int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_size);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Failed to accept connection\n";
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Receive a message from the client
    std::cout << "connection established" << std::endl;
    char buffer[8192];//最长的长度不要超过了,不然可能导致下面依照头来解包失效
    while (true)
    {

        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == SOCKET_ERROR) {
            std::cerr << "Failed to receive data\n";
            closesocket(client_socket);
            closesocket(server_socket);
            WSACleanup();
            return -1;
        }
        if (bytes_received == 0)
        {

        }

        // Print out the received message
        else
        {
            std::vector<std::string> receivedMessages;
            std::queue<Header*> packetQueue;

            int bufferOffset = findSequenceIndex(buffer, bytes_received);
            while (bufferOffset < bytes_received)
            {

                if (bufferOffset + headerlength > bytes_received)
                {
                    // Not enough data in the buffer to parse the header
                    break;
                }

                // Create a temporary header struct pointer at the current buffer offset
                Header* tempHeader = reinterpret_cast<Header*>(&buffer[bufferOffset]);

                // Extract the header fields
                short receivedSeq = tempHeader->sequence;
                short receivedID = tempHeader->Id;
                short receivedLength = tempHeader->length;

                // Determine if there is enough data in the buffer to process the entire packet
                if (bufferOffset + headerlength + receivedLength > bytes_received)
                {
                    // Not enough data in the buffer to process the complete packet
                    break;
                }

                // Allocate memory for the data payload
                char* receivedData = new char[receivedLength];

                // Copy the data payload from the buffer
                std::memcpy(receivedData, &buffer[bufferOffset + headerlength], receivedLength);

                // Update the buffer offset to the next packet
                //bufferOffset += sizeof(Header) + receivedLength;
                bufferOffset += headerlength + receivedLength;
                // Create a header struct to store the unpacked data
                Header* unpackedHeader = new Header;
                unpackedHeader->sequence = receivedSeq;
                unpackedHeader->Id = receivedID;
                unpackedHeader->length = receivedLength;
                unpackedHeader->data = receivedData;

                // Add the unpacked packet to the queue for further processing
                packetQueue.push(unpackedHeader);
            }
            while (!packetQueue.empty())
            {
                Header* packet = packetQueue.front();
                m_logger->processPacket(packet);
                // Don't forget to deallocate memory
                delete[] packet->data;
                delete packet;
                packetQueue.pop();
            }
        }
    }
    // Close the sockets
    closesocket(client_socket);
    closesocket(server_socket);

    // For Windows, clean up the Winsock library
    WSACleanup();

    return 0;
}
