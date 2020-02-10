#include "AbstractModule.h"

AbstractModule::AbstractModule(const QString& id) : 
    QObject(nullptr),
    m_id(id)
{
}

AbstractModule::~AbstractModule() {
}

const QString& AbstractModule::id() {
    return m_id;
}

int AbstractModule::version() {
    return 0;
}

#pragma warning(disable:4100)

void AbstractModule::load(QDir& moduleDir) {}

void AbstractModule::save(QDir& moduleDir) {}

void AbstractModule::render(const Position& from, const Position& to, DomChapter& dom, const QVector<Feature*>& activeFeatures) {}


