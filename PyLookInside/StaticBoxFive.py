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

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer11 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "OF"
        texte1 = wx.StaticText(self, -1, "OF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer11.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe") 
        basicText.SetInsertionPoint(0)
        bsizer11.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer12 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "SF"
        texte1 = wx.StaticText(self, -1, "SF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer12.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self, -1, "O",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer12.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer13 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "ZF"
        texte1 = wx.StaticText(self, -1, "ZF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer13.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "ZF"
        basicText = wx.TextCtrl(self, -1, "---",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer13.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer14 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "AF"
        texte1 = wx.StaticText(self, -1, "AF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer14.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "AF"
        basicText = wx.TextCtrl(self, -1, "1",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer14.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer15 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "PF"
        texte1 = wx.StaticText(self, -1, "PF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer15.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "PF"
        basicText = wx.TextCtrl(self, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer15.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer16 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self, -1, "CF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer16.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self, -1, "2",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer16.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)

        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer17 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "TF"
        texte1 = wx.StaticText(self, -1, "TF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer17.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "TF"
        basicText = wx.TextCtrl(self, -1, "1",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer17.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer18 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self, -1, "IF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer18.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self, -1, "M",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer18.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer19 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self, -1, "DF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer19.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self, -1, "0",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer19.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer20 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "NT"
        texte1 = wx.StaticText(self, -1, "NT",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont)
        texte1.SetForegroundColour("#404040")
        bsizer20.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "NT"
        basicText = wx.TextCtrl(self, -1, "P",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer20.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------

        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "", style=wx.BORDER_NONE)
        bsizer21 = wx.StaticBoxSizer(box, wx.VERTICAL)
        
        # Affiche le texte "RF"
        texte1 = wx.StaticText(self, -1, "RF",
                               style = wx.TE_CENTRE)
        texte1.SetFont(self.normalFont) 
        texte1.SetForegroundColour("#404040")
        bsizer21.Add(texte1, 1, wx.ALL|wx.EXPAND, 0)
        
        # Crée le champ "RF"
        basicText = wx.TextCtrl(self, -1, "2",
                                style = wx.TE_CENTRE)
        basicText.SetFont(self.normalFont)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        bsizer21.Add(basicText, 1, wx.ALL|wx.EXPAND, 0)
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------

        # Crée les Sizer et gére la disposition des widgets
        # Crée des BoxSizer pour chaque widget ou groupe de widgets
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
        topSizer.Add(sizer7, 0, wx.EXPAND | wx.ALL, 0)
        
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

        
