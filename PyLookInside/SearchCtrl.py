# -*- coding: utf8 -*-

# Import packages

import wx                            # This module uses the new wx namespace

#---------------------------------------------------------------------------

class My_SearchCtrl(wx.SearchCtrl):
    def __init__(self, parent, id=-1, value="",
                 pos=wx.DefaultPosition, size=wx.DefaultSize, style=0):
        wx.SearchCtrl.__init__(self, parent, id, value,
                               pos, size, style)
    
        #-------------------------------------------------------------------
        
        self.parent = parent

        #-------------------------------------------------------------------

        fontSize = self.GetFont().GetPointSize()

        # wx.Font(pointSize, family, style, weight, underline, faceName)
        if wx.Platform == "__WXMAC__":
            self.normalFont = wx.Font(fontSize-1, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        elif wx.Platform == "__WXGTK__":
            self.normalFont = wx.Font(fontSize+1, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        else:
            self.normalFont = wx.Font(fontSize+1, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        self.SetFont(self.normalFont)
        self.SetSize(self.GetBestSize())
        
        #-------------------------------------------------------------------

        self.ShowSearchButton(True)
        self.ShowCancelButton(True)

        #-------------------------------------------------------------------
        
        self.SetMenu(self.OnMenu())

        #-------------------------------------------------------------------

        # Bind some events to an events handler
        self.Bind(wx.EVT_SEARCHCTRL_SEARCH_BTN, self.OnSearchBtn, self)
        self.Bind(wx.EVT_SEARCHCTRL_CANCEL_BTN, self.OnCancelBtn, self)
        self.Bind(wx.EVT_TEXT_ENTER, self.OnDoSearch)
        self.Bind(wx.EVT_MENU, self.OnMenu)

    #-----------------------------------------------------------------------
    
    def OnDoSearch(self, event):
        pass


    def OnSearchBtn(self, event):
        pass
    

    def OnCancelBtn(self, event):
        self.Clear()


    def OnMenu(self):
        menu = wx.Menu()
        item = menu.Append(-1, text=u"Prefix :")
        item.Enable(False)
        for txt in [ u"Offset",
                     u"Value" ]:
            menu.Append(-1, txt)

        return menu

    
