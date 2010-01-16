# -*- coding: utf8 -*-

# Import packages

import wx                            # This module uses the new wx namespace
import wx.html
        
#---------------------------------------------------------------------------

class PageCopyright(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
        
        html = wx.html.HtmlWindow(self)
        if "gtk2" in wx.PlatformInfo:
            html.SetStandardFonts()

        html.SetPage(u'''<html><body><div align="center">
        <br>
        <br>
        <h3><font color="#ff9804">PyLookInside v2.64</h3></font>
        <p>Blah ,Blah</font>
        <br>
        <p><b>© Copyright 2009-2010.</b>
        <br>
        <p><b>Sweet Home :</b>
        <br><font color="blue">http://beatrix2004.free.fr/BeaEngine/index.php</font>

        <br>
        <br>License GNU-LGPL version 2.</div></body></html>''')

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(html, 1, wx.EXPAND, 0)

        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------
        
class PageLicence(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

        #-------------------------------------------------------------------
        
        fontSize = self.GetFont().GetPointSize()

        # wx.Font(pointSize, family, style, weight, underline, faceName)
        if wx.Platform == "__WXMAC__":   
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
        
        elif wx.Platform == "__WXGTK__":
            self.normalFont = wx.Font(fontSize+2, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
        
        else:
            self.normalFont = wx.Font(fontSize+2, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
        
        self.SetFont(self.normalFont)

        #-------------------------------------------------------------------

        f = open(u"License/lgpl.txt", "r")
        msg = f.read()
        f.close()

        self.field = wx.TextCtrl(self, -1, value=msg,
                                 style=wx.TE_MULTILINE | wx.TE_READONLY |
                                 wx.TE_LEFT | wx.TE_DONTWRAP)

        self.field.SetFont(self.normalFont)
        self.field.SetSize(self.field.GetBestSize())
        self.field.SetForegroundColour(wx.BLACK)
    
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(self.field, 1, wx.EXPAND, 0)

        self.SetSizer(sizer)
        sizer.Fit(self)

#---------------------------------------------------------------------------

class PageDevelopers(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

        html = wx.html.HtmlWindow(self)
        if "gtk2" in wx.PlatformInfo:
            html.SetStandardFonts()

        html.SetPage(u'''<html><body><div align="center">
        <br>
        <br>
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br></div></body></html>''')
        
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(html, 1, wx.EXPAND, 0)

        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------

class PageThanksTo(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
        
        html = wx.html.HtmlWindow(self)
        if "gtk2" in wx.PlatformInfo:
            html.SetStandardFonts()

        html.SetPage(u'''<html><body><div align="center">        
        <br>
        <br>
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br>- Blah ,Blah
        <br></div></body></html>''')

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(html, 1, wx.EXPAND, 0)

        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------
        
class My_Notebook(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, -1,
                           title=u"About...", size=(500, 400))

        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
        
        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/copyright_Header.png", wx.BITMAP_TYPE_PNG)
        img = wx.StaticBitmap(self)
        img.SetBitmap(bmp)

        #-------------------------------------------------------------------

        notebook = wx.Notebook(self)

        page1 = PageCopyright(notebook)
        page2 = PageLicence(notebook)
        page3 = PageDevelopers(notebook)
        page4 = PageThanksTo(notebook)
        
        notebook.AddPage(page1, u"Copyright")
        notebook.AddPage(page2, u"License")
        notebook.AddPage(page3, u"Developers")
        notebook.AddPage(page4, u"Thanks to")
        
        #-------------------------------------------------------------------
        
        btnOK = wx.Button(self, id=wx.ID_OK, label=u"&OK")
        btnOK.SetDefault()
        
        # Bind the button event to an events handler
        self.Bind(wx.EVT_BUTTON, self.OnOK, btnOK)

        #-------------------------------------------------------------------

        notebookSizer = wx.BoxSizer(wx.HORIZONTAL)
        btnSizer = wx.BoxSizer(wx.HORIZONTAL)
        
        notebookSizer.Add(notebook, 1, wx.TOP | wx.EXPAND, 78)
        btnSizer.Add(btnOK, 0, wx.TOP | wx.BOTTOM | wx.RIGHT, 10)

        #------------
        
        topSizer = wx.BoxSizer(wx.VERTICAL)
        
        topSizer.Add(notebookSizer, 1, wx.EXPAND, 0)
        topSizer.Add(btnSizer, 0, wx.ALIGN_RIGHT)
         
        #------------

        self.SetAutoLayout(True)
        self.SetSizer(topSizer)
        
        #-------------------------------------------------------------------
        
        self.CenterOnParent(wx.BOTH)
        
        #-------------------------------------------------------------------

        btnOK = self.ShowModal()
        self.Destroy()

    #-----------------------------------------------------------------------
        
    def OnCloseWindow(self, event):
        self.Destroy()
         

    def OnOK(self, event):
        self.EndModal(False)

        
