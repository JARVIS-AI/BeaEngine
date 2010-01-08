# -*- coding: utf8 -*-

# Import des modules

import wx


# TODO
        # Paramètre les différents styles de police de caractères
        # Récupère taille et police de l'OS


        
#---------------------------------------------------------------------------

class My_StaticBox(wx.Panel):
    """ Crée la classe des StaticBox. """
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, pos=(0, 20), size=(470, 770))
        
        #-------------------------------------------------------------------

        # Définit un style pour l'ensemble des polices
        if wx.Platform == "__WXMAC__":
            self.font2 = wx.Font(10, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL,
                                 wx.FONTWEIGHT_NORMAL, False, "")

        elif wx.Platform == "__WXGTK__":
            self.font2 = wx.Font(8, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL,
                                 wx.FONTWEIGHT_NORMAL, False, "")

        else:
            self.font2 = wx.Font(8, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL,
                                 wx.FONTWEIGHT_NORMAL, False, "")

        self.SetFont(self.font2)

        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Category"
        box = wx.StaticBox(self, -1, "Instruction. Category :",
                     pos = (10, 10), size = (450, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1,
                               "GENERAL_PURPOSE_INSTRUCTION + CONTROL_TRANSFER",
                               pos=(20, 30), size=(430, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")

        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Mnemonic"
        box = wx.StaticBox(self, -1, "Instruction. Mnemonic :",
                     pos = (10, 59), size = (140, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "", pos=(20, 80),
                               size=(120, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetLabel("jean")
        texte1.SetForegroundColour("#892903")

        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Opcode"
        box = wx.StaticBox(self, -1, "Instruction. Opcode :",
                     pos = (160, 59), size = (140, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000074", pos=(170, 80),
                               size=(120, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")

        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Branch Type"
        box = wx.StaticBox(self, -1, "Instruction. Branch Type :",
                     pos = (310, 59), size = (150, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "je", pos=(320, 80),
                               size=(130, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        #-------------------------------------------------------------------

        # Crée la staticbox "Instruction. Prefixes"
        box = wx.StaticBox(self, -1, "Instruction. Prefixes :",
                     pos = (10, 109), size = (140, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---", pos=(20, 130),
                               size=(120, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")

        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Immediat"
        box = wx.StaticBox(self, -1, "Instruction. Immediat :",
                     pos = (160, 109), size = (140, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---", pos=(170, 130),
                               size = (120, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Implicit Modified Regs"
        box = wx.StaticBox(self, -1, "Implicit Modified Regs :",
                     pos = (310, 109), size = (150, 44))
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "---", pos=(320, 130),
                               size=(130, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Argument n°1"
        box = wx.StaticBox(self, -1, u"Argument n°1 :",
                     pos = (10, 159), size = (450, 190))
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self, -1, "Arg. Type = ", pos=(20, 179))       # v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "NO_ARGUMENT", pos=(85, 179),
                               size=(355, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Access. Mode"
        texte1 = wx.StaticText(self, -1, "Access. Mode = ", pos=(20, 199))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "WRITE", pos=(104, 199),
                               size=(336, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self, -1, "Arg. Mnemonic = ", pos=(20, 219))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(108, 219),
                               size=(332, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self, -1, "Arg. Size = ", pos=(20, 239))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(80, 239),
                               size=(360, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Base Register"
        texte1 = wx.StaticText(self, -1, "Memory. Base Register = ", pos=(20, 259))# v=+20
        texte1.SetFont(self.font2)

        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(148, 259),
                               size=(292, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Index Register"
        texte1 = wx.StaticText(self, -1, "Memory. Index Register = ", pos=(20, 279))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(154, 279),
                               size=(286, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Scale"
        texte1 = wx.StaticText(self, -1, "Memory. Scale = ", pos=(20, 299))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(108, 299),
                               size=(332, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Displacement"
        texte1 = wx.StaticText(self, -1, "Memory. Displacement = ", pos=(20, 319))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(145, 319),
                               size=(295, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Argument n°2"
        box = wx.StaticBox(self, -1, u"Argument n°2 :",
                     pos = (10, 355),size = (450, 190))
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self, -1, "Arg. Type = ", pos=(20, 375))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "CONSTANT_TYPE + RELATIVE",
                               pos=(85, 375), size=(355, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Access. Mode"
        texte1 = wx.StaticText(self, -1, "Access. Mode = ", pos=(20, 395))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "READ", pos=(104, 395),
                               size=(336, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self, -1, "Arg. Mnemonic = ", pos=(20, 415))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "40717Eh", pos=(108, 415),
                               size=(332, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self, -1, "Arg. Size = ", pos=(20, 435))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(80, 435),
                               size=(360, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Base Register"
        texte1 = wx.StaticText(self, -1, "Memory. Base Register = ", pos=(20, 455))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(148, 455),
                               size=(292, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Index Register"
        texte1 = wx.StaticText(self, -1, "Memory. Index Register = ", pos=(20, 475))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(154, 475),
                               size=(286, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Scale"
        texte1 = wx.StaticText(self, -1, "Memory. Scale = ", pos=(20, 495))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(108, 495),
                               size=(332, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Memory. Displacement"
        texte1 = wx.StaticText(self, -1, "Memory. Displacement = ", pos=(20, 515))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(145, 515),
                               size=(295, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Argument n°3"
        box = wx.StaticBox(self, -1, u"Argument n°3 :",
                     pos = (10, 551), size = (450, 90))
        
        # Affiche le texte "Arg. Type"
        texte1 = wx.StaticText(self, -1, "Arg. Type = ", pos=(20, 571))# v=+20
        texte1.SetFont(self.font2)
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "NO_ARGUMENT", pos=(85, 571),
                               size=(355, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Mnemonic"
        texte1 = wx.StaticText(self, -1, "Arg. Mnemonic = ", pos=(20, 591))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "-", pos=(108, 591),
                               size=(332, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")
        
        # Affiche le texte "Arg. Size"
        texte1 = wx.StaticText(self, -1, "Arg. Size = ", pos=(20, 611))# v=+20
        texte1.SetFont(self.font2) 
        
        # Affiche le texte
        texte1 = wx.StaticText(self, -1, "00000000", pos=(80, 611),
                               size=(360, -1), style=wx.ALIGN_LEFT)
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#892903")

        #-------------------------------------------------------------------
        #-------------------------------------------------------------------
        
        # Crée la staticbox "Instruction. Eflag"
        box = wx.StaticBox(self, -1, "Instruction. Eflag :",
                           pos = (10, 647), size = (450, 80))

        #--------------------------------------------------------------------
        
        # Affiche le texte "OF"
        texte1 = wx.StaticText(self, -1, "OF", pos=(40, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self, -1, "M", (40, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe") 
        basicText.SetInsertionPoint(0)
        
        #-------
        
        # Affiche le texte "SF"
        texte1 = wx.StaticText(self, -1, "SF", pos=(70, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "OF"
        basicText = wx.TextCtrl(self, -1, "O", (70, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        
        #-------
        
        # Affiche le texte "ZF"
        texte1 = wx.StaticText(self, -1, "ZF", pos=(100, 667))       # v=+20
        texte1.SetFont(self.font2) 
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "ZF"
        basicText = wx.TextCtrl(self, -1, "---", (100, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)
        
        #-------
        
        # Affiche le texte "AF"
        texte1 = wx.StaticText(self, -1, "AF", pos=(130, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "AF"
        basicText = wx.TextCtrl(self, -1, "1", (130, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------
        
        # Affiche le texte "PF"
        texte1 = wx.StaticText(self, -1, "PF", pos=(160, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "PF"
        basicText = wx.TextCtrl(self, -1, "M", (160, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------
        
        # Affiche le texte "CF"
        texte1 = wx.StaticText(self, -1, "CF", pos=(190, 667))       # v=+20
        texte1.SetFont(self.font2) 
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "CF"
        basicText = wx.TextCtrl(self, -1, "2", (190, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------
        
        # Affiche le texte "TF"
        texte1 = wx.StaticText(self, -1, "TF", pos=(220, 667))       # v=+20
        texte1.SetFont(self.font2) 
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "TF"
        basicText = wx.TextCtrl(self, -1, "1", (220, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------
        
        # Affiche le texte "IF"
        texte1 = wx.StaticText(self, -1, "IF", pos=(250, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "IF"
        basicText = wx.TextCtrl(self, -1, "M", (250, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------
        
        # Affiche le texte "DF"
        texte1 = wx.StaticText(self, -1, "DF", pos=(280, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "DF"
        basicText = wx.TextCtrl(self, -1, "O", (280, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------

        # Affiche le texte "NT"
        texte1 = wx.StaticText(self, -1, "NT", pos=(310, 667))       # v=+20
        texte1.SetFont(self.font2)
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "NT"
        basicText = wx.TextCtrl(self, -1, "P", (310, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

        #-------

        # Affiche le texte "RF"
        texte1 = wx.StaticText(self, -1, "RF", pos=(340, 667))       # v=+20
        texte1.SetFont(self.font2) 
        texte1.SetForegroundColour("#404040")
        
        # Crée le champ "RF"
        basicText = wx.TextCtrl(self, -1, "2", (340, 687),
                                (20, 20), style = wx.TE_CENTRE)
        basicText.SetFont(self.font2)
        basicText.SetBackgroundColour("#edecfe")
        basicText.SetInsertionPoint(0)

