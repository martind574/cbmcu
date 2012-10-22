/***************************************************************
 * Name:      mcupm
 * Purpose:   Code::Blocks plugin
 * Author:    Martin Davey (martind@emverse.co.uk)
 * Created:   2012-10-22
 * Copyright: Martin Davey
 * License:   GPL
 **************************************************************/

#ifndef MCUPM_H_INCLUDED
#define MCUPM_H_INCLUDED

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <cbplugin.h> // for "class cbToolPlugin"

class mcupm : public cbToolPlugin
{
    public:
        /** Constructor. */
        mcupm();
        /** Destructor. */
        virtual ~mcupm();

        /** @brief Execute the plugin.
          *
          * This is the only function needed by a cbToolPlugin.
          * This will be called when the user selects the plugin from the "Plugins"
          * menu.
          */
        virtual int Execute();
    protected:
        /** Any descendent plugin should override this virtual method and
          * perform any necessary initialization. This method is called by
          * Code::Blocks (PluginManager actually) when the plugin has been
          * loaded and should attach in Code::Blocks. When Code::Blocks
          * starts up, it finds and <em>loads</em> all plugins but <em>does
          * not</em> activate (attaches) them. It then activates all plugins
          * that the user has selected to be activated on start-up.\n
          * This means that a plugin might be loaded but <b>not</b> activated...\n
          * Think of this method as the actual constructor...
          */
        virtual void OnAttach();

        /** Any descendent plugin should override this virtual method and
          * perform any necessary de-initialization. This method is called by
          * Code::Blocks (PluginManager actually) when the plugin has been
          * loaded, attached and should de-attach from Code::Blocks.\n
          * Think of this method as the actual destructor...
          * @param appShutDown If true, the application is shutting down. In this
          *         case *don't* use Manager::Get()->Get...() functions or the
          *         behaviour is undefined...
          */
        virtual void OnRelease(bool appShutDown);

        void OnProjectNew(CodeBlocksEvent &event);
};

#endif // MCUPM_H_INCLUDED
