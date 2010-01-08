# -*- coding: utf8 -*-

# Import des modules

import sys
import wx                    # Ce module utilise le nouvel espace de nom wx.
import wx.lib.mixins.listctrl  as  listmix
#import  images

#---------------------------------------------------------------------------

class My_ListCtrl(wx.ListCtrl,
                  listmix.ListCtrlAutoWidthMixin,
                  listmix.ColumnSorterMixin):
    """ Crée la classe de la ListCtrl. """
    def __init__(self, parent):
        wx.ListCtrl.__init__(self, parent, -1,
                             style=wx.LC_REPORT | wx.LC_VIRTUAL |
                             wx.LC_SORT_ASCENDING | wx.LC_SINGLE_SEL |
                             wx.LC_VRULES | wx.BORDER_NONE)
        
        # Ceci redimensionne automatiquement la dernière colonne
        # en récupérant l'espace restant
        listmix.ListCtrlAutoWidthMixin.__init__(self)
        # Permet le tri par ordre alphabétique croissant ou décroissant
        listmix.ColumnSorterMixin.__init__(self, 2)

        #-------------------------------------------------------------------

        # Paramètre les différents styles de police de caractères
        # Récupère taille et police de l'OS
        fontSize = self.GetFont().GetPointSize()

        # wx.Font(pointSize, family, style, weight, underline, faceName)         
        if wx.Platform == "__WXMAC__":
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        elif wx.Platform == "__WXGTK__":
            self.normalFont = wx.Font(fontSize+1, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        else:
            self.normalFont = wx.Font(fontSize+1, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")

        self.SetFont(self.normalFont)

        #--------------------------------------------------------------------

        # Défini la taille des images de la listCtrl
        self.il = wx.ImageList(16, 16)

        # Charge les images        
        # self.idx1 = self.il.Add(images.Smiles.GetBitmap())
        bmp = wx.Bitmap("Bitmaps/listCtrl_Icon.png", wx.BITMAP_TYPE_PNG)
        self.idx1 = self.il.Add(bmp)

        bmp1 = wx.Bitmap("Bitmaps/small_Up_Arrow.png", wx.BITMAP_TYPE_PNG)
        self.sm_up = self.il.Add(bmp1)

        bmp2 = wx.Bitmap("Bitmaps/small_Dn_Arrow.png", wx.BITMAP_TYPE_PNG)
        self.sm_dn = self.il.Add(bmp2)

        self.SetImageList(self.il, wx.IMAGE_LIST_SMALL)
        
        #-------------------------------------------------------------------

        # Ajoute des colonnes et paramètre la largeur de chacune
        self.InsertColumn(0, u"Offset", wx.LIST_FORMAT_LEFT, width=130)
        self.InsertColumn(1, u"Value", wx.LIST_FORMAT_LEFT)

        #-------------------------------------------------------------------

        # Détermine le nombre d'item à afficher
        self.SetItemCount(201)

        #-------------------------------------------------------------------

        # Attribue une couleur aux items
        self.SetForegroundColour("#6a6a66")
        
        # Attribue une couleur aux rangées des items
        self.attributeColor = wx.ListItemAttr()
        self.attributeColor.SetBackgroundColour(wx.Colour(237, 241, 243))  

        #-------------------------------------------------------------------

        # Sélectionne un item par défaut
        self.SetItemState(0, wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)

        #-------------------------------------------------------------------
        
        # Sort by genre (column 2), A->Z ascending order (1)
        self.SortListItems(0, True)    # ou    0, 1

        #-------------------------------------------------------------------
        
        # Lie des événements au gestionnaire d'événements
        self.Bind(wx.EVT_LIST_ITEM_SELECTED, self.OnItemSelected)
        self.Bind(wx.EVT_LIST_ITEM_ACTIVATED, self.OnItemActivated)
        self.Bind(wx.EVT_LIST_COL_CLICK, self.OnColClick)
        
    #----------------------------------------------------------------------- 

    def OnColClick(self,event):
        event.Skip()
        
    def OnItemSelected(self, event):
        """ Item sélectionné. """
        self.currentItem = event.m_itemIndex

    def OnItemActivated(self, event):
        """ Item Activé. """
        self.currentItem = event.m_itemIndex

    def getColumnText(self, index, col):
        """ Item désélectionné. """
        item = self.GetItem(index, col)
        return item.GetText()

    #---------------------------------------------------
    # These methods are callbacks for implementing the
    # "virtualness" of the list...  Normally you would
    # determine the text, attributes and/or image based
    # on values from some external data source, but for
    # this demo we'll just calculate them
    def OnGetItemText(self, item, col):
        return "Item %d, column %d" % (item, col)

    def OnGetItemImage(self, item):
        if item % 1 == 0:
            return self.idx1
        else:
            return -1

    def OnGetItemAttr(self, item):
        """ Attribue une fois sur deux une couleur aux rangées. """

        if item % 1 == 0:    # % 2
            return self.attributeColor
        else:
            return None


    #---------------------------------------------------
    # Matt C, 2006/02/22
    # Here's a better SortItems() method --
    # the ColumnSorterMixin.__ColumnSorter() method already handles the ascending/descending,
    # and it knows to sort on another column if the chosen columns have the same value.

#    def SortItems(self, sorter=cmp):
#        items = list(self.itemDataMap.keys())
#        items.sort(sorter)
#        self.itemIndexMap = items
#         item.sort(sorter)

        
        # redraw the list
#        self.Refresh()

    # Used by the ColumnSorterMixin, see wx/lib/mixins/listctrl.py
    def GetListCtrl(self):
        return self

    # Used by the ColumnSorterMixin, see wx/lib/mixins/listctrl.py
    def GetSortImages(self):
        return (self.sm_dn, self.sm_up)
    
#---------------------------------------------------------------------------
        
class VirtualListPanel1(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)
        
        sizer = wx.BoxSizer(wx.VERTICAL)
                    
        self.list = My_ListCtrl(self)
        sizer.Add(self.list, 1, wx.EXPAND)
        
        self.SetSizer(sizer)
        self.SetAutoLayout(True)

