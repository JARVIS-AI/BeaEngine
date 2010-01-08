# -*- coding: utf8 -*-

# Import des modules

import wx                    # Ce module utilise le nouvel espace de nom wx.
# import images

#---------------------------------------------------------------------------

class My_TaskBarIcon(wx.TaskBarIcon):
    """ Crée la classe de la TaskBarIcon/System Tray. """
    def __init__(self, frame):
        wx.TaskBarIcon.__init__(self)

        #-------------------------------------------------------------------
        
        # Crée une référence du parent        
        self.frame = frame

        #-------------------------------------------------------------------

        # Affiche une icône avec toolTip dans la TaskBar
        # icon = self.MakeIcon(images.Icon_App.GetImage())
        bmp = wx.Image("Icons/icon_App.ico", wx.BITMAP_TYPE_ICO)
        icon = self.MakeIcon(bmp)
        self.SetIcon(icon, tooltip=u"PyLookInside")

        #-------------------------------------------------------------------
        
        # Lie les événements de menus au gestionnaire d'événements        
        self.Bind(wx.EVT_MENU, self.OnTaskBarActivate, id=1)
        self.Bind(wx.EVT_MENU, self.OnTaskBarDeactivate, id=2)
        self.Bind(wx.EVT_MENU, self.OnTaskBarClose, id=3)

    #-----------------------------------------------------------------------
        
    def CreatePopupMenu(self):
        """ Crée un menu dans la TaskBarIcon/Sytem Tray. """  

        # Crée un menu 
        menu = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap au menu
        # bmp = images.Item_Empty.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Empty.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menu, 1, text=u"Afficher PyLookInside")
        item.SetBitmap(bmp)
        menu.AppendItem(item)

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap au menu
        # bmp = images.Item_Empty.GetBitmap()       
        bmp = wx.Bitmap("Bitmaps/item_Empty.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menu, 2, text=u"Masquer PyLookInside")
        item.SetBitmap(bmp)
        menu.AppendItem(item)
        menu.AppendSeparator()  

        #-------------------------------------------------------------------
        
        # Ajoute une bitmap au menu
        # bmp = images.Item_Exit.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/item_Exit.png", wx.BITMAP_TYPE_PNG)
                        
        if True or "wxMSW" in wx.PlatformInfo:
            font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
            font.SetWeight(wx.BOLD)
            
        item = wx.MenuItem(menu, 3, text=u"Quitter PyLookInside")
        item.SetBitmap(bmp)
        item.SetFont(font)
        menu.AppendItem(item)

        return menu

    #-----------------------------------------------------------------------
    
    def MakeIcon(self, img):
        """
        The various platforms have different requirements
        for the icon size...
        """

        if "wxMSW" in wx.PlatformInfo:
            img = img.Scale(16, 16)
        elif "wxGTK" in wx.PlatformInfo:
            img = img.Scale(22, 22)
        # wxMac can be any size upto 128x128, so leave the source img alone....
        icon = wx.IconFromBitmap(img.ConvertToBitmap() )
        return icon


    def OnTaskBarActivate(self, event):
        """ Affiche l'application. """

        if not self.frame.IsShown():
            self.frame.Show()

        
    def OnTaskBarDeactivate(self, event):
        """ Masque l'application. """
        
        if self.frame.IsShown():
            self.frame.Hide()
            

    def OnTaskBarClose(self, event):
        """ Quitte l'application. """

        self.frame.Close()

