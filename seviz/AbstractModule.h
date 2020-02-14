#pragma once
#include <QObject>
#include <QSet>
#include <QString>
#include <QDir>
#include "Feature.h"
#include "BookModels.h"
#include "EventHandler.h"
#include "DomChapter.h"

class AbstractModule : public QObject
{
    Q_OBJECT

    friend class ModuleManager;
public:
    AbstractModule(const QString& id);
    virtual ~AbstractModule();

    virtual const QString& id();
    virtual int version();
    virtual QList<Feature> features() = 0;

    virtual void load(QDir& moduleDir);
    virtual void save(QDir& moduleDir);

public slots:
    virtual void render(const Position& from, const Position& to, DomChapter& dom, const QVector<Feature*>& activeFeatures);

private:
    QString m_id;
    ModuleManager* m_engine;
};