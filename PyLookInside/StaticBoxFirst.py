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

        # Crée la staticbox "Instruction. Category"
        box = wx.StaticBox(self, -1, "Instruction. Category :")
        bsizer1 = wx.StaticBoxSizer(box, wx.VERTICAL)
       
        # Affiche le texte
        texte1 = wx.StaticText(self, -1,
                               "GENERAL_PURPOSE_INSTRUCTION + CONTROL_TRANSFER",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer1.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Mnemonic"
        box = wx.StaticBox(self, -1, "Instruction. Mnemonic :")
        bsizer2 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "jean",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer2.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Opcode"
        box = wx.StaticBox(self, -1, "Instruction. Opcode :")
        bsizer3 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000074",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer3.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Branch Type"
        box = wx.StaticBox(self, -1, "Instruction. Branch Type :")
        bsizer4 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "je",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer4.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Prefixes"
        box = wx.StaticBox(self, -1, "Instruction. Prefixes :")
        bsizer5 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer5.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Immediat"
        box = wx.StaticBox(self, -1, "Instruction. Immediat :")
        bsizer6 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer6.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Implicit Modified Regs"
        box = wx.StaticBox(self, -1, "Implicit Modified Regs :")
        bsizer7 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---",
                               style=wx.ALIGN_LEFT)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#892903")
        bsizer7.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
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

        # Crée une BoxSizer VERTICALE générale
        topSizer = wx.BoxSizer(wx.VERTICAL)

        # Ajoute les BoxSizer dans la BoxSizer générale 
        topSizer.Add(sizer1, 0, wx.EXPAND | wx.ALL, 0)
        topSizer.Add(sizer2, 0, wx.EXPAND | wx.ALL, 0)
        topSizer.Add(sizer3, 0, wx.EXPAND | wx.ALL, 0)
        
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

        
