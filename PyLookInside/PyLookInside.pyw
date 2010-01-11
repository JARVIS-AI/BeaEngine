#!/usr/bin/env python
# -*- coding: utf8 -*-

"""
1) Indique à Linux où se trouve l'interpréteur Python et
   permet un lancement du script par double-clic.
2) Prise en charge des caractères spéciaux..
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
import ListCtrlVirtual
#import StaticBoxThreePanel
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
        self.SetStatusText(u"Bienvenue à PyLookInside !", 0)
      
        #-------------------------------------------------------------------                        
        #-------------------------------------------------------------------
        
        # Déclare les méthodes d'initialisation simplifiées
        self.createMenuBar()
        self.createToolBar()
        self.createSplitter()
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
                           text=u"&Ouvrir\tCtrl+O",
                           help=u"Ouvre un fichier.")
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnFileOpen, item)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_Exit.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Exit.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Quitter\tCtrl+Q",
                           help=u"Quitte l'application.")
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
                           text=u"En&rouler\tF3",
                           help=u"Réduit l'application à sa barre de titre.")
        item.SetBitmap(bmp)
        menuView.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnRoll, item)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap
        # bmp = images.Item_Unroll.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Unroll.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menuView, -1,
                           text=u"&Dérouler\tF4",
                           help=u"Restaure l'application à sa taille initiale.")
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
                           text=u"À p&ropos...\tCtrl+A",
                           help=u"Au sujet de cette application.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnAbout, item)

        #-------------------------------------------------------------------

        # Ajoute une bitmap
        # bmp = images.Item_Note.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Note.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"Me&mento\tCtrl+M",
                           help=u"Pense-bête.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnMemento, item)

        #-------------------------------------------------------------------

        # Ajoute une bitmap
        # bmp = images.Item_Help.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Help.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"Aide\tCtrl+H",
                           help=u"Aide en ligne.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Lie l'événement de menu au gestionnaire d'événements
        self.Bind(wx.EVT_MENU, self.OnHelp, item)

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Place les menus dans la barre de menus
        menuBar.Append(menuFile, title=u"&Fichier")
        menuBar.Append(menuView, title=u"&Affichage")
        menuBar.Append(menuHelp, title=u"&?")
        
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
        self.toolbar.AddLabelTool(20, u"Ouvrir",
                                  wx.Bitmap("Bitmaps/tb_Open.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Ouvre un fichier.")
        self.toolbar.AddSeparator()
                                  #images.Tb_Disassemble.GetBitmap(),
        self.toolbar.AddLabelTool(21, u"Désassembler",
                                  wx.Bitmap("Bitmaps/tb_Disassemble.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Lance le désassemblage.")
        self.toolbar.AddSeparator()
                                  #images.Tb_About.GetBitmap(),
        self.toolbar.AddLabelTool(22, u"A propos",
                                  wx.Bitmap("Bitmaps/tb_About.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Au sujet de cette application.")
        self.toolbar.AddSeparator()
                                  #images.Tb_Note.GetBitmap(),
        self.toolbar.AddLabelTool(23, u"Memento",
                                  wx.Bitmap("Bitmaps/tb_Note.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"Coucou !",
                                  longHelp=u"Pense-bête.")
        self.toolbar.AddSeparator()
                                  #images.Tb_Help.GetBitmap(),
        self.toolbar.AddLabelTool(24, u"Aide",
                                  wx.Bitmap("Bitmaps/tb_Help.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"",
                                  longHelp=u"Aide en ligne.")
        self.toolbar.AddSeparator()
                                  #images.Tb_Print.GetBitmap(),
        self.toolbar.AddLabelTool(25, u"Imprimer",
                                  wx.Bitmap("Bitmaps/tb_Print.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"meuh",
                                  longHelp=u"Fait une capture écran de l'application.")
        self.toolbar.AddSeparator()
                                  #images.Tb_Quit.GetBitmap(),
        self.toolbar.AddLabelTool(26, u"Quitter",
                                  wx.Bitmap("Bitmaps/tb_Quit.png", wx.BITMAP_TYPE_PNG),
                                  shortHelp=u"meuh",
                                  longHelp=u"Quitte l'application.")
        self.toolbar.AddSeparator()
        self.toolbar.AddSeparator()
                                  # Crée le  searchCtrl
        self.searchCtrl = SearchCtrl.My_SearchCtrl(self.toolbar, 50,
                                                   value="0040711E")     
        self.toolbar.AddControl(self.searchCtrl) # Ajoute le searchCtrl d
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

        # Crée le splitter        
        self.sp1 = wx.SplitterWindow(self.panel, style=wx.NO_3D |
                                     wx.SP_3D | wx.SP_LIVE_UPDATE |
                                     wx.TAB_TRAVERSAL)
       
         # Lie des événements au gestionnaire d'événements
        # self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_SPLITTER_DCLICK, self.OnDoubleClick, id=-1)

        #-------------------------------------------------------------------
        
        # Crée des panels à l'intérieur du splitter
        self.leftpanel = wx.Panel (self.sp1, style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)  #BORDER_NONE
        self.rightpanel = wx.Panel (self.sp1, style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)  #BORDER_NONE


        #-------------------------------------------------------------------

        # Paramètre les différents styles de police de caractères
        # Récupère taille et police de l'OS
        fontSize = self.GetFont().GetPointSize()

        # wx.Font(pointSize, family, style, weight, underline, faceName) 
        if wx.Platform == "__WXMAC__":
            self.normalFont = wx.Font(fontSize-3, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")          

        elif wx.Platform == "__WXGTK__":
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
              
        else:
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
         
        self.SetFont(self.normalFont)

#-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Category"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Category :")
        bsizer1 = wx.StaticBoxSizer(box, wx.VERTICAL)
       
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1,
                               "GENERAL_PURPOSE_INSTRUCTION + CONTROL_TRANSFER",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer1.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Mnemonic"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Mnemonic :")
        bsizer2 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "jean",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer2.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Opcode"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Opcode :")
        bsizer3 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "00000074",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer3.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Branch Type"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Branch Type :")
        bsizer4 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "je",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer4.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Prefixes"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Prefixes :")
        bsizer5 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer5.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Immediat"
        box = wx.StaticBox(self.rightpanel, -1, "Instruction. Immediat :")
        bsizer6 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer6.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Implicit Modified Regs"
        box = wx.StaticBox(self.rightpanel, -1, "Implicit Modified Regs :")
        bsizer7 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self.rightpanel, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer7.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)

#-------------------------------------------------------------------

          # Crée la staticbox "Argument n°1"
        box = wx.StaticBox(self.rightpanel, -1, u"Argument n°1 :")
        bsizer8 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Type = NO_ARGUMENT",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Access. Mode"
        texte1 = wx.StaticText(self.rightpanel, -1, "Access. Mode = WRITE",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Mnemonic = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Size = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Base Register"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Base Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Index Register"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Index Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Scale"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Scale = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Displacement"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Displacement = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer8.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)

#-------------------------------------------------------------------

        # Crée la staticbox "Argument n°2"
        box = wx.StaticBox(self.rightpanel, -1, u"Argument n°2 :")
        bsizer9 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Type = CONSTANT_TYPE + RELATIVE",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Access. Mode"
        texte1 = wx.StaticText(self.rightpanel, -1, "Access. Mode = READ",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Mnemonic = 40717Eh",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Size = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Base Register"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Base Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Index Register"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Index Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Scale"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Scale = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Displacement"
        texte1 = wx.StaticText(self.rightpanel, -1, "Memory. Displacement = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)

#-------------------------------------------------------------------

        # Crée la staticbox "Argument n°3"
        box = wx.StaticBox(self.rightpanel, -1, u"Argument n°3 :")
        bsizer10 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Type = NO_ARGUMENT")
        texte1.SetFont(self.normalFont)
        bsizer10.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Mnemonic = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer10.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self.rightpanel, -1, "Arg. Size = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer10.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)

#-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer11 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "OF"
        texte1 = wx.StaticText(self.rightpanel, -1, "OF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer11.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe") 
        basicText.SetInsertionPoint(0)
        bsizer11.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer12 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "SF"
        texte1 = wx.StaticText(self.rightpanel, -1, "SF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer12.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "O",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer12.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer13 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "ZF"
        texte1 = wx.StaticText(self.rightpanel, -1, "ZF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer13.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "ZF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "---",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer13.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer14 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "AF"
        texte1 = wx.StaticText(self.rightpanel, -1, "AF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer14.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "AF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "1",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer14.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer15 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "PF"
        texte1 = wx.StaticText(self.rightpanel, -1, "PF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer15.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "PF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer15.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer16 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self.rightpanel, -1, "CF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer16.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "2",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer16.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer17 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "TF"
        texte1 = wx.StaticText(self.rightpanel, -1, "TF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer17.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "TF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "1",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer17.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer18 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self.rightpanel, -1, "IF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer18.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer18.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer19 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self.rightpanel, -1, "DF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer19.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "0",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer19.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer20 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "NT"
        texte1 = wx.StaticText(self.rightpanel, -1, "NT",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer20.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "NT"
        basicText = wx.TextCtrl(self.rightpanel, -1, "P",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer20.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self.rightpanel, -1, "", style=wx.BORDER_NONE)
        bsizer21 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "RF"
        texte1 = wx.StaticText(self.rightpanel, -1, "RF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer21.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "RF"
        basicText = wx.TextCtrl(self.rightpanel, -1, "2",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer21.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------

        # Crée les Sizer et gére la disposition des widgets
        # Crée des BoxSizer pour chaque widget ou groupe de widgets
        sizer1 = wx.BoxSizer(wx.HORIZONTAL)
        sizer1.Add(bsizer1, 1, wx.EXPAND | wx.ALL, 0) # 5

      
        sizer2 = wx.BoxSizer(wx.HORIZONTAL)
        sizer2.Add(bsizer2, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer2.Add(bsizer3, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer2.Add(bsizer4, 1, wx.EXPAND | wx.ALL, 0) # 5

        sizer3 = wx.BoxSizer(wx.HORIZONTAL)
        sizer3.Add(bsizer5, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer3.Add(bsizer6, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer3.Add(bsizer7, 1, wx.EXPAND | wx.ALL, 0) # 5

        sizer4 = wx.BoxSizer(wx.HORIZONTAL)
        sizer4.Add(bsizer8, 1, wx.EXPAND | wx.ALL, 0) # 5

        sizer5 = wx.BoxSizer(wx.HORIZONTAL)
        sizer5.Add(bsizer9, 1, wx.EXPAND | wx.ALL, 0) # 5

        sizer6 = wx.BoxSizer(wx.HORIZONTAL)
        sizer6.Add(bsizer10, 1, wx.EXPAND | wx.ALL, 0) # 5

        sizer7 = wx.BoxSizer(wx.HORIZONTAL)
        sizer7.Add(bsizer11, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer12, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer13, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer14, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer15, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer16, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer17, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer18, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer19, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer20, 1, wx.EXPAND | wx.ALL, 0) # 5
        sizer7.Add(bsizer21, 1, wx.EXPAND | wx.ALL, 0) # 5
        
        # Crée une BoxSizer VERTICALE générale
        topSizer = wx.BoxSizer(wx.VERTICAL)

        # Ajoute les BoxSizer dans la BoxSizer générale 
        topSizer.Add(sizer1, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer2, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer3, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer4, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer5, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer6, 0, wx.EXPAND | wx.ALL, 5)
        topSizer.Add(sizer7, 0, wx.EXPAND | wx.ALL, 5)

        self.rightpanel.SetSizer(topSizer)
        topSizer.Fit(self.rightpanel)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée une instance de la classe My_ListCtrl
        self.list = ListCtrlVirtual.My_ListCtrl(self.leftpanel)        

        # Donne le Focus au contrôle
        self.list.SetFocus()

        self.sp1.SetMinimumPaneSize(1)

        # Ajoute les contrôles dans le splitter
        self.sp1.SplitVertically(self.leftpanel, self.rightpanel)  # , -500

        # Paramètre la taille par défaut du splitter
        self.sp1.SetSashPosition(350, True)

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

        #--------------
        #--------------
        
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

        
        
        # Crée une BoxSizer VERTICALE principale qui englobe tous les widgets
#        topSizer = wx.BoxSizer(wx.HORIZONTAL)
        
        # Ajoute les Sizer dans la BoxSizer VERTICALE principale
#        topSizer.Add(splitSizer, 1, wx.EXPAND, 0) 
#        topSizer.Add(listCtrlSizer, 1, wx.EXPAND | wx.LEFT |
#                     wx.RIGHT | wx.BOTTOM, 0)     

        # SetSizeHints(minW, minH, maxW, maxH)
        # self.SetSizeHints(800, 640, -1, -1)

        #--------------
        #--------------

#        # Sizer sans panel
#        self.SetAutoLayout(True)
#        # Set the sizer
#        self.SetSizer(topSizer)
#        # Fit ourselves to the sizer
#        topSizer.Fit(self)

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

        pass    
    #-----------------------------------------------------------------------
        
    def OnPass(self, event):
        """ Regroupe les événements vides dans le gestionnaire d'événements. """
        pass
    
    #-----------------------------------------------------------------------
        
    def OnDoubleClick(self, event):
        """ Applique au splitter sa taille par défaut. """   
        size = self.GetSize()
#        self.sp1.SetSashPosition(size.x / 2)
        self.sp1.SetSashPosition(350, True)
        
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


