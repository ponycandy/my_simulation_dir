#include "node.h"

Node::Node()
{

}

Node::Node(int realId) : m_realId(realId), m_jdSum(0.0), m_wdSum(0.0), m_count(0) {}

void Node::addPoint(double jd, double wd, int Id, const QString &type, int origFid) {
    m_jdSum += jd;
    m_wdSum += wd;
    m_count++;
    m_ids.insert(Id);
    m_types.insert(type);
    m_origFids.insert(origFid);
}

double Node::avgJd() const { return m_count > 0 ? m_jdSum / m_count : 0.0; }

double Node::avgWd() const { return m_count > 0 ? m_wdSum / m_count : 0.0; }

int Node::realId() const { return m_realId; }

QSet<int> Node::ids() const { return m_ids; }

QSet<QString> Node::types() const { return m_types; }

QSet<int> Node::origFids() const { return m_origFids; }
