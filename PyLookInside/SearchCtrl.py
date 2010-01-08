# -*- coding: utf8 -*-

# Import des modules

import wx                    # Ce module utilise le nouvel espace de nom wx.

#---------------------------------------------------------------------------

class My_SearchCtrl(wx.SearchCtrl):
    """ Crée la classe du SearchCtrl. """    
    def __init__(self, parent, id=-1, value="",
                 pos=wx.DefaultPosition, size=wx.DefaultSize, style=0):
        wx.SearchCtrl.__init__(self, parent, id, value,
                               pos, size, style)
        
        #-------------------------------------------------------------------
        
        # Crée une référence du parent
        self.parent = parent

        #-------------------------------------------------------------------
        
        # Paramètre les différents styles de police de caractères
        # Récupère taille et police de l'OS
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

        # Affiche le bouton "Rechercher"
        self.ShowSearchButton(True)
        
        # Affiche le bouton "Annuler"
        self.ShowCancelButton(True)

        # Affiche le menu
        self.SetMenu(self.OnMenu())

        # Lie une tooltip au champ
        self.SetToolTipString(tip=u"Faites Ctrl+Entrée "
                              "pour changer de champ.")

        # Lie des événements au gestionnaire d'événements
        self.Bind(wx.EVT_SEARCHCTRL_SEARCH_BTN, self.OnSearchBtn, self)
        self.Bind(wx.EVT_SEARCHCTRL_CANCEL_BTN, self.OnCancelBtn, self)
        self.Bind(wx.EVT_TEXT_ENTER, self.OnDoSearch)
        self.Bind(wx.EVT_MENU, self.OnMenu)   

    #-----------------------------------------------------------------------
    
    def OnDoSearch(self, event):
        """ Lance la recherche automatique. """

        pass


    def OnSearchBtn(self, event):

        pass
    

    def OnCancelBtn(self, event):
        """ Efface le contenu du champ Saisie/Recherche. """

        self.Clear()


    def OnMenu(self):
        """ Crée et affiche le menu. """
        
        menu = wx.Menu()
        item = menu.Append(-1, text=u"Préfixes de dossiers :")
        item.Enable(False)
        for txt in [ u"Offset",
                     u"Value",
                     u"Offset",
                     u"Value",
                     u"Offset",
                     u"Value" ]:
            menu.Append(-1, txt)

        return menu

