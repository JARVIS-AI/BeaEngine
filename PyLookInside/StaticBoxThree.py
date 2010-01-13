# -*- coding: utf8 -*-

# Import des modules

import wx

#---------------------------------------------------------------------------

class My_StaticBox(wx.Panel):
    """ Crée la classe des StaticBox. """
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        # Donne une couleur au fond de la Frame
        # self.SetBackgroundColour(wx.NamedColour("LIGHTGREY"))  #LIGHTGREY

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

        # Crée la staticbox "Argument n°2"
        box = wx.StaticBox(self, -1, u"Argument n°2 :")
        bsizer9 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self, -1, "Arg. Type = CONSTANT_TYPE + RELATIVE",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Access. Mode"
        texte1 = wx.StaticText(self, -1, "Access. Mode = READ",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self, -1, "Arg. Mnemonic = 40717Eh",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self, -1, "Arg. Size = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Base Register"
        texte1 = wx.StaticText(self, -1, "Memory. Base Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Index Register"
        texte1 = wx.StaticText(self, -1, "Memory. Index Register = -",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Scale"
        texte1 = wx.StaticText(self, -1, "Memory. Scale = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Affiche le texte "Memory. Displacement"
        texte1 = wx.StaticText(self, -1, "Memory. Displacement = 00000000",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        bsizer9.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------

        # Crée les Sizer et gére la disposition des widgets
        # Crée des BoxSizer pour chaque widget ou groupe de widgets
        sizer5 = wx.BoxSizer(wx.HORIZONTAL)
        sizer5.Add(bsizer9, 1, wx.EXPAND | wx.ALL, 0) # 5

        # Crée une BoxSizer VERTICALE générale
        topSizer = wx.BoxSizer(wx.VERTICAL)

        # Ajoute les BoxSizer dans la BoxSizer générale 
        topSizer.Add(sizer5, 0, wx.EXPAND | wx.ALL, 0)
        
        # Sizer sans panel
        # self.SetAutoLayout(True)
        # Set the sizer
        self.SetSizer(topSizer)
        # Fit ourselves to the sizer
        topSizer.Fit(self)
        



###################################################################

        # Détermine la taille maxi/mini du conteneur :
#        self.SetMaxSize((600, 200))
#        self.SetMinSize((600, 100))


#        # SetSizeHints(minW, minH, maxW, maxH)
#        self.SetSizeHints(250,300,500,400)

        
