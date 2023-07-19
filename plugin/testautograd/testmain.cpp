#include "testmain.h"
#include "testautogradActivator.h"
#include "variablexl.h"
#include "costfunc.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "iostream"
Testmain::Testmain(QObject *parent)
    : QObject{parent}
{
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");


    m_service= testautogradActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    variablexl *VAR;
    VAR=new variablexl(5);
    std::shared_ptr<ifopt::VariableSet> VARptr(VAR);
    m_service->AddVariableSet(VARptr);

    costfunc *tcost;
    tcost=new costfunc;
    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr(tcost);
    m_service->AddCostSet(Dtcostptr);

    m_service->start_crack();
    double v=tcost->GetCost();
    qDebug()<<v;
}
