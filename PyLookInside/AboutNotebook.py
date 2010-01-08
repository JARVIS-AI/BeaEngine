# -*- coding: utf8 -*-

# Import des modules

import wx                    # Ce module utilise le nouvel espace de nom wx.
import wx.html
        
#---------------------------------------------------------------------------

class PageCopyright(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
         
        # Affiche le texte
        html = wx.html.HtmlWindow(self)
        if "gtk2" in wx.PlatformInfo:
            html.SetStandardFonts()

        html.SetPage(u'''<html><body><div align="center">
        <br>
        <br>
        <h3><font color="#ff9804">PyLookInside v2.64</h3></font>
        <p>PyLookInside est une interface GUI de désassemblage écrite en <font color=\"red\">wxPython.</font>
        <br>
        <p><b>© Copyright 2009-2010  |  BeaCorporation, Inc.</b>
        <br>
        <br>Page d'accueil : <font color="blue">http://127.0.0.1/download1.php</font>
        <br>
        <br>Licence GNU-LGPL version 2.</div></body></html>''') # % VersionInfos.LICENSE_STRING

        html.SetBackgroundColour(wx.WHITE)
        
        # Crée une BoxSizer HORIZONTALE
        sizer = wx.BoxSizer(wx.HORIZONTAL)

        # Ajoute les widgets dans la BoxSizer HORIZONTALE        
        sizer.Add(html, 1, wx.EXPAND, 0)

        # Paramètre le sizer
        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------
        
class PageLicense(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

        #-------------------------------------------------------------------

        # Paramètre les différents styles de police de caractères
        # Récupère taille et police de l'OS
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

        # Ouvre le fichier texte
        f = open(u"Licence/lgpl.txt", "r")
        msg = f.read()
        f.close()

        # Crée le TextCtrl et affiche son contenu texte      
        self.field = wx.TextCtrl(self, -1, value=msg,
                                 style=wx.TE_MULTILINE | wx.TE_READONLY |
                                 wx.TE_LEFT | wx.TE_DONTWRAP)

        self.field.SetFont(self.normalFont)
        self.field.SetSize(self.field.GetBestSize())
        self.field.SetForegroundColour(wx.BLACK)
        
        # Crée une BoxSizer HORIZONTALE
        sizer = wx.BoxSizer(wx.HORIZONTAL)

        # Ajoute les widgets dans la BoxSizer HORIZONTALE        
        sizer.Add(self.field, 1, wx.EXPAND, 0)

        # Paramètre le sizer
        self.SetSizer(sizer)
        # Fit ourselves to the sizer
        sizer.Fit(self)

#---------------------------------------------------------------------------

class PageDeveloper(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

        # Affiche le texte
        html = wx.html.HtmlWindow(self)
        if "gtk2" in wx.PlatformInfo:
            html.SetStandardFonts()

        html.SetPage(u'''<html><body><div align="center">
        <br>
        <br>
        <br>- Beatrix (librairie, dll, connection...)
        <br>- Zig (interface GUI)
        <br>- Igor (portabilité sur Linux)</div></body></html>''')
        
        # Donne une couleur de fond à l'onglet
        html.SetBackgroundColour("yellow")
        
        # Crée une BoxSizer HORIZONTALE
        sizer = wx.BoxSizer(wx.HORIZONTAL)

        # Ajoute les widgets dans la BoxSizer HORIZONTALE        
        sizer.Add(html, 1, wx.EXPAND, 0)

        # Paramètre le sizer
        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------

class PageThanks(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
         
        # Affiche le texte
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

        # Donne une couleur de fond à l'onglet
        html.SetBackgroundColour(wx.WHITE)
        
        # Crée une BoxSizer HORIZONTALE
        sizer = wx.BoxSizer(wx.HORIZONTAL)

        # Ajoute les widgets dans la BoxSizer HORIZONTALE        
        sizer.Add(html, 1, wx.EXPAND, 0)

        # Paramètre le sizer
        self.SetSizer(sizer)
        sizer.Fit(self)
        
#---------------------------------------------------------------------------
        
class My_Notebook(wx.Dialog):
    """ Crée la classe Notebook. """
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, -1, title=u"À propos...", size=(500, 400))

        # Lie l'événement de fermeture au gestionnaire d'événements
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
        
        #-------------------------------------------------------------------

        # Affiche une image dans la dialog
        # bmp = images.Logo_Note.GetBitmap()
        bmp = wx.Bitmap("Bitmaps/copyright_Header.png", wx.BITMAP_TYPE_PNG)
        img = wx.StaticBitmap(self)
        img.SetBitmap(bmp)

        #-------------------------------------------------------------------        
        # Crée un Notebook dans la dialog
        notebook = wx.Notebook(self)

        # Create the page windows as children of the notebook
        page1 = PageCopyright(notebook)
        page2 = PageLicense(notebook)
        page3 = PageDeveloper(notebook)
        page4 = PageThanks(notebook)
        
        # Add the pages to the notebook with the label to show on the tab
        notebook.AddPage(page1, u"Copyright")
        notebook.AddPage(page2, u"Licence")
        notebook.AddPage(page3, u"Développeurs")
        notebook.AddPage(page4, u"Remerciements")
        
        #-------------------------------------------------------------------
        
        # Ajoute un bouton 
        btnOK = wx.Button(self, id=wx.ID_OK, label=u"&OK")

        # Paramètre le bouton par défaut
        btnOK.SetDefault()
        
        # Lie l'événement de bouton au gestionnaire d'événements
        self.Bind(wx.EVT_BUTTON, self.OnOK, btnOK)

        #-------------------------------------------------------------------

        # Crée des BoxSizer HORIZONTALES
        notebookSizer = wx.BoxSizer(wx.HORIZONTAL)
        btnSizer = wx.BoxSizer(wx.HORIZONTAL)

        # Ajoute les widgets dans les BoxSizer appropriées
        # (l'ordre d'affichage doit être respecté)
        # sizer.Add(sizer, proportion, flag, border)
        notebookSizer.Add(notebook, 1, wx.TOP | wx.EXPAND, 78)
        btnSizer.Add(btnOK, 0, wx.TOP | wx.BOTTOM | wx.RIGHT, 10)

        # Crée une BoxSizer VERTICALE principale
        # qui englobe tous les widgets
        topSizer = wx.BoxSizer(wx.VERTICAL)
        
        # Ajoute les BoxSizer HORIZONTALES dans la
        # BoxSizer VERTICALE principale
        topSizer.Add(notebookSizer, 1, wx.EXPAND, 0)
        topSizer.Add(btnSizer, 0, wx.ALIGN_RIGHT)
         
        #-------------------------------------------------------------------
        
        # Finally, put the notebook in a sizer for the panel to manage the layout
        # Sizer sans panel
        self.SetAutoLayout(True)
        # Paramètre le sizer
        self.SetSizer(topSizer)
        
        #-------------------------------------------------------------------
        
        # Affiche et centre My_Notebook sur le Parent
        self.CenterOnParent(wx.BOTH)
        
        #-------------------------------------------------------------------

        # Définis la fenêtre comme fenêtre modale (elle garde la main)        
        btnOK = self.ShowModal()
        self.Destroy()

    #-----------------------------------------------------------------------
        
    def OnCloseWindow(self, event):
        self.Destroy()
         

    def OnOK(self, event):
        self.EndModal(False)

