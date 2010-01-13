#!/usr/bin/env python
# -*- coding: utf8 -*-

"""
1) Indique à Linux où se trouve l'interpréteur Python et
   permet un lancement du script par double-clic.
2) Prise en charge des caractères spéciaux.
"""


#########################################################################
# Name      :  PyLookInside.py                                           #
# Version   :  2.6.4                                                    #
# Authors   :  Beatrix (library, connection...) &                       #
#              Zig (interface GUI)                                      #
# Created   :  December 2009                                            #
# Copyright :  (c) 2009-2010 Beatrix, BeaCorporation Inc                #
# License   :  wxWindows License                                        #
# About     :  PyTemplateDataBase was built using Python 2.6.4,         #
#              wxPython 2.8.10.1 unicode, and wxWindows                 #
#########################################################################


# Import des modules

import wxversion
wxversion.select("2.8")     # Le script démarre uniquement sous wx.Python 2.8

import os

try:
    import wx                    # Ce module utilise le nouvel espace de nom wx.
except ImportError:
    raise ImportError, u"Le module wx.Python unicode est requi pour lancer l'application."

# import images
import VersionInfos
import CustomSplashScreen
import TaskBarIcon
import time
import locale
import SearchCtrl
import Splitter
import ListCtrlVirtual
import StaticBoxFirst
import StaticBoxSecond
import StaticBoxThree
import StaticBoxFour
import StaticBoxFive
import AboutNotebook
import MementoProvider
from WilcardList import *

# System Constants
#---------------------


#---------------------------------------------------------------------------

class My_CustomStatusBar(wx.StatusBar):
    """ Crée la classe de la barre d'état personnalisée. """
    def __init__(self, parent):
        wx.StatusBar.__init__(self, parent, -1)

        #-------------------------------------------------------------------
        
        # Crée une référence du parent
        self.parent = parent
        
        #-------------------------------------------------------------------
        
        # Détermine le nombre de fields
        self.SetFieldsCount(2)

        #-------------------------------------------------------------------
        
        # Règle la largeur de chaque field
        self.SetStatusWidths([-7, -3])

        #-------------------------------------------------------------------
        
        self.sizeChanged = False

        # Lie des événements au gestionnaire d'événements
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_IDLE, self.OnIdle)

        #-------------------------------------------------------------------
        
        # Crée un timer pour l'horloge du dernier field
        self.timer = wx.PyTimer(self.Notify)
        # Update every 1000 milliseconds
        self.timer.Start(1000)
        self.Notify()
        
    #-----------------------------------------------------------------------

    # Handles events from the timer we started in __init__().
    # We're using it to drive a 'clock' in field 2 (the third field).
    def Notify(self):
        """ Timer event """

        # Permet de savoir en quelle langue est votre PC
        locale.setlocale(locale.LC_ALL,'')
        temp = time.strftime('Le %a %d %b %Y - %Hh%M')

        # Le texte du 2ème field vaut 1
        self.SetStatusText(temp, 1)


    def OnSize(self, evt):
        self.Reposition()  # for normal size events

        # Set a flag so the idle time handler will also do the repositioning.
        # It is done this way to get around a buglet where GetFieldRect is not
        # accurate during the EVT_SIZE resulting from a frame maximize.
        self.sizeChanged = True


    def OnIdle(self, evt):
        if self.sizeChanged:
            self.Reposition()


    def Reposition(self):
        self.sizeChanged = False

#---------------------------------------------------------------------------

class My_Frame(wx.Frame):
    """ Crée la classe de la frame principale. """
    isRolled = 0
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id,
                          title=u"PyLookInside %s"
                          % VersionInfos.VERSION_STRING,
                          size=(830, 675),  # 860, 675
                          style=wx.DEFAULT_FRAME_STYLE |
                          wx.NO_FULL_REPAINT_ON_RESIZE |
                          wx.TAB_TRAVERSAL) # wx.WANTS_CHARS)

        # Lie l'événement de fermeture au gestionnaire d'événements
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)      

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------

        # Crée le conteneur (doit être déclaré avant
        # les méthodes d'initialisation simplifiées)
        self.panel = wx.Panel(self, -1)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée une instance de la classe My_CustomStatusBar        
        self.sb = My_CustomStatusBar(self)
        self.SetStatusBar(self.sb)
        self.SetStatusText(u"Welcome to PyLookInside !", 0)                 # u"Bienvenue à PyLookInside !"
      
        #-------------------------------------------------------------------                        
        #-------------------------------------------------------------------
        
        # Déclare les méthodes d'initialisation simplifiées
        self.createMenuBar()
        self.createToolBar()
        self.createSplitter()
        self.createListCtrl()
        self.createStaticBox()
        self.createTaskBarIcon()
        self.doLayout()
        
        #-------------------------------------------------------------------                   
        #-------------------------------------------------------------------

        # Centre la frame à l'écran
        self.CenterOnScreen()

    #-----------------------------------------------------------------------       

    def createMenuBar(self):
        """ Crée la barre de menus et les Menus. """  

        # Crée la barre de menus       
        menuBar = wx.MenuBar()

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute un menu "Fichier"
        menuFile = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_Open.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Open.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Open\tCtrl+O",                           # u"&Ouvrir\tCtrl+O"
                           help=u"Open a file.")                            # u"Ouvre un fichier."
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnFileOpen, item)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_Exit.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Exit.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"E&xit\tCtrl+Q",                           # u"&Quitter\tCtrl+Q"
                           help=u"Exit the application.")                  # u"Quitte l'application."
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnClose, item)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute un menu "Affichage"
        menuView = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_RollUp.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_RollUp.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menuView, -1,
                           text=u"&Roll\tF3",                               # u"En&rouler\tF3"
                           help=u"Minimize the application to this titleBar.")      # u"Réduit l'application à sa barre de titre." 
        item.SetBitmap(bmp)
        menuView.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnRoll, item)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_Unroll.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Unroll.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menuView, -1,
                           text=u"&UnRoll\tF4",                                      # u"&Dérouler\tF4"
                           help=u"Restore the application to this initial size.")     # u"Restaure l'application à sa taille initiale."
        item.SetBitmap(bmp)
        menuView.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnUnRoll, item)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute un menu "Aide"
        menuHelp = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_About.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_About.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"&About...\tCtrl+A",                         # u"À p&ropos...\tCtrl+A"
                           help=u"About this application.")                   # u"Au sujet de cette application."
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnAbout, item)

        #-------------------------------------------------------------------

        # Ajoute une bitmap
        # bmp = images.Item_Note.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Note.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"Me&mento\tCtrl+M",                           # u"Me&mento\tCtrl+M"
                           help=u"Pense-bête.")                                # u"Pense-bête."
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnMemento, item)

        #-------------------------------------------------------------------

        # Ajoute une bitmap
        # bmp = images.Item_Help.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Help.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"&Help\tCtrl+H",                              # u"Aide\tCtrl+H"
                           help=u"Help online.")                            # u"Aide en ligne."
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnHelp, item)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Place les menus dans la barre de menus
        menuBar.Append(menuFile, title=u"&File")                               # u"&Fichier"
        menuBar.Append(menuView, title=u"&View")                               # u"&Affichage"
        menuBar.Append(menuHelp, title=u"&?")                                  # u"&?"
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Attache la barre de menus à la fenêtre
        self.SetMenuBar(menuBar)

    #----------------------------------------------------------------------- 

    def createToolBar(self):        
        """ Crée la barre d'outils. """

        # Crée la barre d'outils
        self.toolbar = self.CreateToolBar(wx.TB_HORIZONTAL | wx.NO_BORDER |
                                          wx.TB_FLAT | wx.TB_TEXT |
                                          wx.NO_FULL_REPAINT_ON_RESIZE)
        self.toolbar.SetBackgroundColour(wx.NamedColour("LIGHTGRAY"))

        toolSize = (24, 24)
        self.toolbar.SetToolBitmapSize(toolSize)

        # Ajoute un bouton
                                  #images.Tb_Open.GetBitmap(),
        self.toolbar.AddLabelTool(20, u"Open",                                                 # u"Ouvrir"
                                  wx.Bitmap("Bitmaps/tb_Open.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Open a file.")                                 # u"Ouvre un fichier."
        self.toolbar.AddSeparator()
                                  #images.Tb_Disassemble.GetBitmap(),
        self.toolbar.AddLabelTool(21, u"Désassembler",                                           # u"Désassembler"
                                  wx.Bitmap("Bitmaps/tb_Disassemble.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Lance le désassemblage.")                           # u"Lance le désassemblage."
        self.toolbar.AddSeparator()
                                  #images.Tb_About.GetBitmap(),
        self.toolbar.AddLabelTool(22, u"About",                                               # u"A propos
                                  wx.Bitmap("Bitmaps/tb_About.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"About this application.")                    # u"Au sujet de cette application."
        self.toolbar.AddSeparator()
                                  #images.Tb_Note.GetBitmap(),
        self.toolbar.AddLabelTool(23, u"Memento",                                                # u"Memento"
                                  wx.Bitmap("Bitmaps/tb_Note.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"Coucou !",
                                  longHelp=u"Pense-bête.")                                       # u"Pense-bête."
        self.toolbar.AddSeparator()
                                  #images.Tb_Help.GetBitmap(),
        self.toolbar.AddLabelTool(24, u"Help",                                                   # u"Aide"
                                  wx.Bitmap("Bitmaps/tb_Help.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Help online.")                                    # u"Aide en ligne."
        self.toolbar.AddSeparator()
                                  #images.Tb_Print.GetBitmap(),
        self.toolbar.AddLabelTool(25, u"Screenshot",                                               # u"Imprimer"
                                  wx.Bitmap("Bitmaps/tb_Print.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"meuh",
                                  longHelp=u"Fait une capture écran de l'application.")          # u"Fait une capture écran de l'application."
        self.toolbar.AddSeparator()
                                  #images.Tb_Quit.GetBitmap(),
        self.toolbar.AddLabelTool(26, u"Exit",                                                # u"Quitter"
                                  wx.Bitmap("Bitmaps/tb_Quit.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"meuh",
                                  longHelp=u"Exit the application.")                             # u"Quitte l'application."
        self.toolbar.AddSeparator()
        self.toolbar.AddSeparator()
                                  # Crée le  searchCtrl
        self.searchCtrl = SearchCtrl.My_SearchCtrl(self.toolbar, 50,
                                                   value="0040711E")     
        self.toolbar.AddControl(self.searchCtrl) # Ajoute le searchCtrl
        self.toolbar.AddSeparator()        
        self.toolbar.AddSeparator()
        
        # Affiche la ToolBar  
        self.toolbar.Realize()
        
        # Lie les événements d'outils au gestionnaire d'événements
        self.Bind(wx.EVT_TOOL, self.OnFileOpen, id=20)
        self.Bind(wx.EVT_TOOL, self.OnDisassemble, id=21)
        self.Bind(wx.EVT_TOOL, self.OnAbout, id=22)
        self.Bind(wx.EVT_TOOL, self.OnMemento, id=23)
        self.Bind(wx.EVT_TOOL, self.OnHelp, id=24)
        self.Bind(wx.EVT_TOOL, self.OnPrint, id=25)
        self.Bind(wx.EVT_TOOL, self.OnClose, id=26)

    #-----------------------------------------------------------------------

    def createSplitter(self):
        """ Crée le splitter. """

        # Crée une instance de la classe My_Splitter
        self.sp1 = Splitter.My_Splitter(self.panel)

        #-------------------------------------------------------------------
        
        # Crée des panels à l'intérieur du splitter
        self.leftpanel = wx.Panel (self.sp1, style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)  #BORDER_NONE
        self.rightpanel = wx.Panel (self.sp1, style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)  #BORDER_NONE

        # Ajoute les contrôles dans le splitter
        self.sp1.SplitVertically(self.leftpanel, self.rightpanel)  # , -500

    #-----------------------------------------------------------------------
       
    def createListCtrl(self):
        """ Crée la liste virtuelle. """

        # Crée une instance de la classe My_ListCtrl
        self.list = ListCtrlVirtual.My_ListCtrl(self.leftpanel)        

        # Donne le Focus au contrôle
        self.list.SetFocus()     
        
    #-----------------------------------------------------------------------

    def createStaticBox(self):
        """ Crée la StaticBox. """

        # Crée une instance de la classe My_StaticBox
        self.stbx1 = StaticBoxFirst.My_StaticBox(self.rightpanel)
        self.stbx2 = StaticBoxSecond.My_StaticBox(self.rightpanel)
        self.stbx3 = StaticBoxThree.My_StaticBox(self.rightpanel)
        self.stbx4 = StaticBoxFour.My_StaticBox(self.rightpanel)
        self.stbx5 = StaticBoxFive.My_StaticBox(self.rightpanel)
        
    #-----------------------------------------------------------------------
        
    def doLayout(self):
        """ Crée les Sizer et gére la disposition des widgets. """

        # Crée des Sizer pour chaque widget ou groupe de widgets   
#        scrollHorSizer = wx.BoxSizer(wx.HORIZONTAL)
#        scrollVerSizer = wx.BoxSizer(wx.VERTICAL)
        listHorSizer = wx.BoxSizer(wx.HORIZONTAL)
        listVerSizer   = wx.BoxSizer(wx.VERTICAL)

        #--------------
        
        # Ajoute les widgets dans les BoxSizer appropriées
        # (l'ordre d'affichage doit être respecté)
        # sizer.Add(sizer, proportion, flag, border)
#        scrollHorSizer.Add(self.scroll, 1, wx.EXPAND)
#        scrollVerSizer.Add(scrollHorSizer, 1, wx.EXPAND)
        listHorSizer.Add(self.list, 1, wx.EXPAND)
        listVerSizer.Add(listHorSizer, 1, wx.EXPAND)

        #-------------------------------------------------------------------

        # Gére la disposition des widgets StaticBox
        # Crée les Sizer et gére la disposition des widgets
        # Crée des BoxSizer pour chaque widget ou groupe de widgets
        sizer1 = wx.BoxSizer(wx.HORIZONTAL)
        sizer2 = wx.BoxSizer(wx.HORIZONTAL)
        sizer3 = wx.BoxSizer(wx.HORIZONTAL)
        sizer4 = wx.BoxSizer(wx.HORIZONTAL)
        sizer5 = wx.BoxSizer(wx.HORIZONTAL)
        
        # Ajoute les widgets dans les BoxSizers appropriées 
        sizer1.Add(self.stbx1, 1, wx.EXPAND | wx.ALL, 0)
        sizer2.Add(self.stbx2, 1, wx.EXPAND | wx.ALL, 0)
        sizer3.Add(self.stbx3, 1, wx.EXPAND | wx.ALL, 0)
        sizer4.Add(self.stbx4, 1, wx.EXPAND | wx.ALL, 0)
        sizer5.Add(self.stbx5, 1, wx.EXPAND | wx.ALL, 0)
        
        # Crée une BoxSizer VERTICALE générale
        topSizer = wx.BoxSizer(wx.VERTICAL)

        # Ajoute les BoxSizer dans la BoxSizer générale 
        topSizer.Add(sizer1, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer2, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer3, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer4, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer5, 0, wx.EXPAND | wx.ALL, 3)

        self.rightpanel.SetSizer(topSizer)
        topSizer.Fit(self.rightpanel)

        #-------------------------------------------------------------------
                
        # Gére les sizers et la disposition des widgets        
        self.leftpanel.SetAutoLayout(True)
        self.rightpanel.SetAutoLayout(True)

        self.leftpanel.SetSizer(listVerSizer)
 #       self.rightpanel.SetSizer(scrollVerSizer)

        listVerSizer.Fit(self.leftpanel)
#        scrollVerSizer.Fit(self.rightpanel)

        #--------------
        #--------------

        # Crée une BoxSizer VERTICALE générale qui ajoute
        # un espace en guise de bordure extérieure
        borderSizer = wx.BoxSizer(wx.VERTICAL)

        #--------------

        # Ajoute les BoxSizer dans la BoxSizer générale   
        borderSizer.Add(self.sp1, 1, wx.EXPAND | wx.ALL , 0)
        
        #--------------
        #--------------
        
        # Sizer avec panel
#        self.panel.SetAutoLayout(True)
        # Set the sizer
        self.panel.SetSizer(borderSizer)
        # Fit ourselves to the sizer
        borderSizer.Fit(self.panel)

        # SetSizeHints(minW, minH, maxW, maxH)
        # self.SetSizeHints(800, 640, -1, -1)


    #-----------------------------------------------------------------------      

    def OnFileOpen(self, event):
        """Affiche la fenêtre de recherche de fichier"""

        dlg = wx.FileDialog(self,
                            message=u"Sélectionner un fichier :",
                            defaultDir=os.getcwd(),
                            defaultFile=u"",
                            wildcard=wildcard,
                            style=wx.OPEN | wx.MULTIPLE | wx.CHANGE_DIR)

        # Show the dialog and retrieve the user response. If it is the OK response, 
        # process the data.
        if dlg.ShowModal()== wx.ID_OK:
            # This returns a Python list of files that were selected.
            paths = dlg.GetPaths()

        # Destroy the dialog. Don't do this until you are done with it!
        # BAD things can happen otherwise!
        dlg.Destroy()

    #-----------------------------------------------------------------------
        
    def OnDisassemble(self, event):
        """ Lance le désassemblage. """
        pass
    
    #-----------------------------------------------------------------------     

    def OnAbout(self, event):
        """ Affiche la fenêtre A propos. """

        # Crée une instance de la classe My_Notebook
        self.notebook = AboutNotebook.My_Notebook(self)

    #-----------------------------------------------------------------------   
        
    def OnMemento(self, event):
        """ Affiche la fenêtre du Memento. """
        
        # Crée une instance de la classe My_Memento
        self.memento = MementoProvider.My_Memento(self)

    #-----------------------------------------------------------------------
        
    def OnHelp(self, event):
        """ Affiche le contenu de l'aide en ligne. """

        pass

    #-----------------------------------------------------------------------
        
    def OnPrint(self, event):
        """ Fait une capture écran de l'appplication. """

#    def TakeScreenShot(self, rect):
#      """ Takes a screenshot of the screen at give pos & size (rect). """

        #Create a DC for the whole screen area
        dcScreen = wx.ScreenDC()
       
        #Create a Bitmap that will later on hold the screenshot image
        #Note that the Bitmap must have a size big enough to hold the screenshot
        #-1 means using the current default colour depth
        bmp = wx.EmptyBitmap(rect.width, rect.height)

        #Create a memory DC that will be used for actually taking the screenshot
        memDC = wx.MemoryDC()

        #Tell the memory DC to use our Bitmap
        #all drawing action on the memory DC will go to the Bitmap now
        memDC.SelectObject(bmp)

        #Blit (in this case copy) the actual screen on the memory DC
        #and thus the Bitmap
        memDC.Blit( 0, #Copy to this X coordinate
                    0, #Copy to this Y coordinate
                    rect.width, #Copy this width
                    rect.height, #Copy this height
                    dcScreen, #From where do we copy?
                    rect.x, #What's the X offset in the original DC?
                    rect.y  #What's the Y offset in the original DC?
                    )

        #Select the Bitmap out of the memory DC by selecting a new
        #uninitialized Bitmap
        memDC.SelectObject(wx.NullBitmap)

        return bmp
    
    #-----------------------------------------------------------------------
        
    def OnPass(self, event):
        """ Regroupe les événements vides dans le gestionnaire d'événements. """
        pass
    
    #-----------------------------------------------------------------------
        
#    def OnDoubleClick(self, event):
#        """ Applique au splitter sa taille par défaut. """   
#        size = self.GetSize()
#        self.sp1.SetSashPosition(size.x / 2)
#        self.sp1.SetSashPosition(350, True)
        
#    def OnSize(self, event):
#        size = self.GetSize()
#        self.sp1.SetSashPosition(size.x / 2)
#        event.Skip()
        
    #-----------------------------------------------------------------------

    def OnRoll(self, event):
        """ Enroule la fenêtre My_Frame. """

        if self.isRolled == 1:
            return
        self.isRolled = 1

        # Récupére taille et position de la frame
        # pos, size = self.GetPosition(), self.GetSize()
        self.pos1 = self.GetPosition()
        self.size1 = self.GetSize()
        
        if wx.Platform == "__WXMAC__":
            self.SetSize((-1, 22))
           
        elif wx.Platform == "__WXGTK__":
            self.SetSize((-1, 0))
            
        else:
            self.SetSize((-1, 0))


    def OnUnRoll(self, event):
        """ Déroule la fenêtre My_Frame. """

        self.isRolled = 0

        # Récupére taille et position de la frame
        # pos, size = self.GetPosition(), self.GetSize()
        self.pos2 = self.GetPosition()
        self.size2 = self.GetSize()
        
        if wx.Platform == "__WXMAC__":
            self.SetSize(self.size1)
            
        elif wx.Platform == "__WXGTK__":
            self.SetSize(self.size1)
            
        else:
            self.SetSize(self.size1)
     
    #-----------------------------------------------------------------------

    def createTaskBarIcon(self):        
        """ Crée l'icône de la barre des tâches (système tray). """

        # Crée une instance de la classe My_TaskBarIcon
        self.tskic = TaskBarIcon.My_TaskBarIcon(self)

    #-----------------------------------------------------------------------
        
    def OnClose(self, event):
        """ Ferme l'application. """
        # Triggers wx.EVT_CLOSE event and hence onCloseWindow()
        self.Close(True)

        
    def OnCloseWindow(self, event):
        """ Quitte et détruit l'application. """

        # Dialog to verify exit 
        dlg = wx.MessageDialog(self,
                               message=u"Voulez-vous vraiment quitter l'application ?",
                               caption=u"Quitter",
                               style=wx.YES_NO | wx.ICON_QUESTION)

        if dlg.ShowModal() == wx.ID_YES:
            if self.tskic is not None:
                self.tskic.Destroy()
                
            self.sb.timer.Stop()
            del self.sb.timer
            self.Destroy()

        dlg.Destroy()

#---------------------------------------------------------------------------
      
class My_App(wx.App):
    """ Toutes les applications wx.Windows doivent avoir une classe dérivée de wx.App. """
    # wx.Windows appelle cette méthode pour initialiser l'application

    # def __init__(self, redirect=False):
    #     print("App __init__")
    #     wx.App.__init__(self, redirect)

    def OnInit(self):
        
        # Create and show the splash screen.  It will then create 
        # and show the main frame when it is time to do so
        wx.SystemOptions.SetOptionInt("mac.window-plain-transition", 1)

        # Normally when using a SplashScreen you would create it, show
        # it and then continue on with the applicaiton's
        # initialization, finally creating and showing the main
        # application window(s).  In this case we have nothing else to
        # do so we'll delay showing the main frame until later (see
        # ShowMain above) so the users can see the SplashScreen effect        
        self.splash = CustomSplashScreen.My_SplashScreen()
        self.splash.Show()

        # Renvoie un indicateur de réussite
        return True   
        
#---------------------------------------------------------------------------

def main():

    # Crée une instance de la classe wx.App
    app = My_App(redirect=False)    # redirect=True/False
       
    # Démarrage du gestionnaire d'événements (boucle principale)
    app.MainLoop()

#----------------------------------------------------------------------------

if __name__ == '__main__':
    __name__ = 'Main'
    main()





######################################################################
    
     
#        # Sizer sans panel
#        self.SetSizer(topSizer)
#        topSizer.Fit(self)
#        self.Layout()

# OU

#        # Sizer sans panel         
#        self.SetAutoLayout(True)
#        self.SetSizer(topSizer)
#        topSizer.Layout()

######################################################################
        
        # Affiche le texte du 1er field (le 1er field vaut 0)
        #self.SetStatusText("Bienvenue !", 0)

        #-------------------------------------------------------------------
        
#        self.dpc = wx.DatePickerCtrl(self, size=(120,-1),
#                                     style = wx.DP_DEFAULT 
#                                     | wx.DP_DROPDOWN)  # calendar
#                                     #| wx.DP_SHOWCENTURY)
#                                     #| wx.DP_ALLOWNONE)   # case
#        # self.Bind(wx.EVT_DATE_CHANGED, self.OnDateChanged, dpc)

######################################################################

        
        # Crée le conteneur (doit être déclaré avant
        # les méthodes d'initialisation simplifiées)
#        self.panel = wx.Panel(self, 1)

        # Donne une couleur au conteneur   
#        self.panel.SetBackgroundColour(wx.NamedColour("LIGHTGREY"))
        
######################################################################


#And then, for the widget you want to take the screenshot (it can be
#also the main frame), you can do something like:

#bmp = self.TakeScreenShot(self.GetRect())
#img = bmp.ConvertToImage()
#fileName = "myImage.png"
#img.SaveFile(fileName, wx.BITMAP_TYPE_PNG) 
