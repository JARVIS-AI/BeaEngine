# -*- coding: utf8 -*-

"""

Copyright 2006-2009, BeatriX

This file is part of BeaEngine.
 
BeaEngine is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BeaEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with BeaEngine.  If not, see <http://www.gnu.org/licenses/>.

"""

# Import packages

import wx                            # This module uses the new wx namespace

#---------------------------------------------------------------------------

class My_Splitter(wx.SplitterWindow):
    def __init__(self, parent, id=-1, proportion=0.66, size=wx.DefaultSize):
        wx.SplitterWindow.__init__(self, parent, id, wx.Point(0, 0), size,
                                   style=wx.NO_3D | wx.SP_3D |
                                   wx.SP_LIVE_UPDATE | wx.TAB_TRAVERSAL)

        #-------------------------------------------------------------------
        
        self.parent = parent
        
        #-------------------------------------------------------------------
        
        # The minimum size of a pane
        self.SetMinimumPaneSize(1)

        self.proportion = proportion
        if not 0 < self.proportion < 1:
            raise ValueError, "proportion value for Splitter must be between 0 and 1."
        self.ResetSash()

        # Bind some events to an events handler
        self.Bind(wx.EVT_SPLITTER_DCLICK, self.OnDoubleClick, id=-1)
        self.Bind(wx.EVT_SPLITTER_SASH_POS_CHANGED, self.OnSashChanged, id=id)
        # Hack to set sizes on first paint event
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        # self.Bind(wx.EVT_SIZE, self.OnSize)
        self.firstpaint = True

    #-----------------------------------------------------------------------
        
    def SplitVertically(self, win1, win2):
        if self.GetParent() is None: return False
        return wx.SplitterWindow.SplitVertically(self, win1, win2,
                int(round(self.GetParent().GetSize().GetWidth() * self.proportion)))


    def GetExpectedSashPosition(self):
        if self.GetSplitMode() == wx.SPLIT_HORIZONTAL:
            tot = max(self.GetMinimumPaneSize(),self.GetParent().GetClientSize().height)
        else:
            tot = max(self.GetMinimumPaneSize(),self.GetParent().GetClientSize().width)
        return int(round(tot * self.proportion))


    def ResetSash(self):
        # self.SetSashPosition(self.GetExpectedSashPosition())
        self.SetSashPosition(350, True)


    def OnDoubleClick(self, event):
        size = self.GetSize()
        self.SetSashPosition(350, True)


    def OnSashChanged(self, event):
        "We'll change self.proportion now based on where user dragged the sash."
        pos = float(self.GetSashPosition())
        if self.GetSplitMode() == wx.SPLIT_HORIZONTAL:
            tot = max(self.GetMinimumPaneSize(),self.GetParent().GetClientSize().height)
        else:
            tot = max(self.GetMinimumPaneSize(),self.GetParent().GetClientSize().width)
        self.proportion = pos / tot
        event.Skip()


    def OnPaint(self,event):
        if self.firstpaint:
            if self.GetSashPosition() != self.GetExpectedSashPosition():
                self.ResetSash()
            self.firstpaint = False
        event.Skip()


    # def OnReSize(self, event):
    #     "Window has been resized, so we need to adjust the sash based on self.proportion."
    #     self.ResetSash()
    #     event.Skip()

    
