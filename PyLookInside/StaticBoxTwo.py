# -*- coding: utf8 -*-

# Import packages

import wx                            # This module uses the new wx namespace

#---------------------------------------------------------------------------

class My_StaticBox(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        #-------------------------------------------------------------------
        
        self.parent = parent
        
        #-------------------------------------------------------------------

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

        box = wx.StaticBox(self, -1, u"Argument n°1 :")
        bsizer = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        texte1 = wx.StaticText(self, -1, "Arg. Type = NO_ARGUMENT",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Access. Mode = WRITE",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Arg. Mnemonic = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Arg. Size = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Memory. Base Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Memory. Index Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Memory. Scale = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        texte1 = wx.StaticText(self, -1, "Memory. Displacement = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont) 
        bsizer.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(bsizer, 1, wx.EXPAND | wx.ALL, 0)

        #----------
        
        topSizer = wx.BoxSizer(wx.VERTICAL)
        topSizer.Add(sizer, 0, wx.EXPAND | wx.ALL, 0)

        #----------

        self.SetSizer(topSizer)
        topSizer.Fit(self)

        
