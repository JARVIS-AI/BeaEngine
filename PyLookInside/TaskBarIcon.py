# -*- coding: utf8 -*-

# Import packages

import wx                            # This module uses the new wx namespace

#---------------------------------------------------------------------------

class My_TaskBarIcon(wx.TaskBarIcon):
    def __init__(self, frame):
        wx.TaskBarIcon.__init__(self)

        #-------------------------------------------------------------------
        
        self.frame = frame

        #-------------------------------------------------------------------

        bmp = wx.Image("Icons/icon_App.ico", wx.BITMAP_TYPE_ICO)
        icon = self.MakeIcon(bmp)
        self.SetIcon(icon, tooltip=u"PyLookInside")

        #-------------------------------------------------------------------

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnTaskBarActivate, id=1)
        self.Bind(wx.EVT_MENU, self.OnTaskBarDeactivate, id=2)
        self.Bind(wx.EVT_MENU, self.OnTaskBarClose, id=3)

    #-----------------------------------------------------------------------
        
    def CreatePopupMenu(self):
        menu = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Empty.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menu, 1, text=u"Show PyLookInside")
        item.SetBitmap(bmp)
        menu.AppendItem(item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Empty.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menu, 2, text=u"Hide PyLookInside")
        item.SetBitmap(bmp)
        menu.AppendItem(item)
        menu.AppendSeparator()  

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Exit.png", wx.BITMAP_TYPE_PNG)
                        
        if True or "wxMSW" in wx.PlatformInfo:
            font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
            font.SetWeight(wx.BOLD)
            
        item = wx.MenuItem(menu, 3, text=u"Quit PyLookInside")
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
        if not self.frame.IsShown():
            self.frame.Show()

        
    def OnTaskBarDeactivate(self, event):
        if self.frame.IsShown():
            self.frame.Hide()
            

    def OnTaskBarClose(self, event):
        self.frame.Close()

        
