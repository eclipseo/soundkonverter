
#ifndef REPLAYGAINPLUGIN_H
#define REPLAYGAINPLUGIN_H

#include <kcoreaddons_export.h>
#include <QVariantList>

#include "backendplugin.h"

#include <QMap>
#include <KUrl>

class ReplayGainPlugin;


struct ReplayGainPipe
{
    QString codecName;

    ReplayGainPlugin *plugin;
    bool enabled; // can we use this conversion pipe? (all needed backends installed?)
    int rating;
    QString problemInfo; // howto message, if a backend is missing
};


class KCOREADDONS_EXPORT ReplayGainPluginItem : public BackendPluginItem
{
    Q_OBJECT
public:
    explicit ReplayGainPluginItem( QObject *parent );
    virtual ~ReplayGainPluginItem();

    struct Data // additional data
    {
        int fileCount;
        int processedFiles;
        float lastFileProgress;
    } data;
};


/** @author Daniel Faust <hessijames@gmail.com> */
class KCOREADDONS_EXPORT ReplayGainPlugin : public BackendPlugin
{
    Q_OBJECT
public:
    enum ApplyMode {
        Add = 0,
        Remove = 1,
        Force = 2
    };

    explicit ReplayGainPlugin( QObject *parent );
    virtual ~ReplayGainPlugin();

    virtual QString type() const;

    virtual QList<ReplayGainPipe> codecTable() = 0;

    /** adds replaygain to one or more files */
    virtual int apply( const KUrl::List& fileList, ApplyMode mode = Add ) = 0;
};

#define K_EXPORT_SOUNDKONVERTER_REPLAYGAIN(libname, classname) \
        K_EXPORT_COMPONENT_FACTORY( soundkonverter_replaygain_##libname, KGenericFactory<classname>("soundkonverter_replaygain_" #libname) )

#endif // REPLAYGAINPLUGIN_H
