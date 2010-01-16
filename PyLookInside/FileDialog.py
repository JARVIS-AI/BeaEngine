# -*- coding: utf8 -*-

# Import packages

import os
import wx                            # This module uses the new wx namespace

from WilcardList import *

#---------------------------------------------------------------------------

class My_FileDialog(wx.FileDialog):
    def __init__(self, parent,):
        wx.FileDialog.__init__(self, parent,
                               message=u"Chosse a file",
                               defaultDir=os.getcwd(),
                               defaultFile=u"",
                               wildcard=wildcard,
                               pos=wx.DefaultPosition,
                               style=wx.OPEN | wx.MULTIPLE | wx.CHANGE_DIR)
        
        # Show the dialog and retrieve the user response. If it is the OK response, 
        # process the data.
        if self.ShowModal()== wx.ID_OK:
            # This returns a Python list of files that were selected.
            paths = self.GetPaths()

        # Destroy the dialog. Don't do this until you are done with it!
        # BAD things can happen otherwise!
        self.Destroy()


