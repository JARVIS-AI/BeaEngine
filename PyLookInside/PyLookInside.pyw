#!/usr/bin/env python
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

#########################################################################
# Name      :  PyLookInside.py                                          #
# Version   :  4.0                                                      #
# Authors   :  Sigman                                                   #
# Created   :  December 2009                                            #
# Copyright :  © Copyright 2009-2010  |  BeatriX                        #
# License   :  wxWindows License                                        #
# About     :  PyTemplateDataBase was built using Python 2.6.4,         #
#              wxPython 2.8.10.1 unicode, and wxWindows                 #
#########################################################################


# Import packages

import wxversion
wxversion.select("2.8-unicode")  # Launch the script only from wx.Python 2.8

import sys
#import os

try:
    import wx                        # This module uses the new wx namespace
except ImportError:
    raise ImportError, u"The wxPython unicode module is required to run this program."

import VersionInfos
import SplashScreen
import ToolBar
import StatusBar
import TaskBarIcon
import Splitter
import ListCtrlVirtual
import StaticBoxOne
import StaticBoxTwo
import StaticBoxThree
import StaticBoxFour
import StaticBoxFive
import AboutNotebook
import MementoProvider
import FileDialog
import webbrowser


# System Constants

#---------------------------------------------------------------------------

class My_Frame(wx.Frame):
    isRolled = 0
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id,
                          title=u"PyLookInside %s"
                          % VersionInfos.VERSION_STRING,
                          pos=wx.DefaultPosition,
                          size=(830, 673),
                          style=wx.DEFAULT_FRAME_STYLE |
                          wx.NO_FULL_REPAINT_ON_RESIZE |
                          wx.TAB_TRAVERSAL)
        
        # Bind the event close to an events handler
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        #-------------------------------------------------------------------

        # self.SetBackgroundColour(wx.NamedColour("LIGHTGREY"))
        self.SetBackgroundColour("LIGHTGREY")    
        #-------------------------------------------------------------------
        
        self.createMenuBar()
        self.createToolBar()
        self.createStatusBar()
        self.createTaskBarIcon()
        self.createSplitter()
        self.createListCtrl()
        self.createStaticBox()
        self.doLayout()
        
        #-------------------------------------------------------------------

        self.CenterOnScreen()

    #-----------------------------------------------------------------------

    def createMenuBar(self):
        menuBar = wx.MenuBar()

        #-------------------------------------------------------------------
        
        menuFile = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Open.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Open\tCtrl+O",
                           help=u"Display the open file dialog.")
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnFileOpen, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Disassemble.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Disassemble\tCtrl+D",
                           help=u"Launch the disassembling.")
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)
        menuFile.AppendSeparator()
        
        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnDisassemble, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Print.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Screen Shot\tCtrl+P",
                           help=u"Frame screen shot.")
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)
        menuFile.AppendSeparator()
        
        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnScreenShot, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Exit.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuFile, -1,
                           text=u"&Quit\tCtrl+Q",
                           help=u"Quit the application.")
        item.SetBitmap(bmp)
        menuFile.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnClose, item)

        #-------------------------------------------------------------------

        menuView = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_RollUp.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menuView, -1,
                           text=u"&Roll\tF3",
                           help=u"Minimize the application to this titleBar.")
        item.SetBitmap(bmp)
        menuView.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnRoll, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Unroll.png", wx.BITMAP_TYPE_PNG)
                        
        item = wx.MenuItem(menuView, -1,
                           text=u"&UnRoll\tF4",
                           help=u"Restore the application to this initial size.")
        item.SetBitmap(bmp)
        menuView.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnUnRoll, item)
        
        #-------------------------------------------------------------------
        
        menuHelp = wx.Menu(style=wx.MENU_TEAROFF)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_About.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"&About...\tCtrl+A",
                           help=u"About this application.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnAbout, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Note.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"Me&mento\tCtrl+M",
                           help=u"Little reminder.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnMemento, item)

        #-------------------------------------------------------------------

        bmp = wx.Bitmap("Bitmaps/item_Help.png", wx.BITMAP_TYPE_PNG)
        
        item = wx.MenuItem(menuHelp, -1,
                           text=u"Online &help\tCtrl+H",
                           help=u"Online help.")
        item.SetBitmap(bmp)
        menuHelp.AppendItem(item)

        # Bind the menu event to an events handler
        self.Bind(wx.EVT_MENU, self.OnlineHelp, item)

        #-------------------------------------------------------------------
        
        menuBar.Append(menuFile, title=u"&File")
        menuBar.Append(menuView, title=u"&View")
        menuBar.Append(menuHelp, title=u"&?")
        
        #-------------------------------------------------------------------
        
        self.SetMenuBar(menuBar)

    #----------------------------------------------------------------------- 

    def createToolBar(self):        
        self.tb = ToolBar.My_Toolbar(self)
        self.SetToolBar(self.tb)

        # Bind some events to an events handler
        self.Bind(wx.EVT_TOOL, self.OnFileOpen, id=20)
        self.Bind(wx.EVT_TOOL, self.OnDisassemble, id=21)
        self.Bind(wx.EVT_TOOL, self.OnScreenShot, id=22)
        self.Bind(wx.EVT_TOOL, self.OnAbout, id=23)
        self.Bind(wx.EVT_TOOL, self.OnMemento, id=24)
        self.Bind(wx.EVT_TOOL, self.OnlineHelp, id=25)
        self.Bind(wx.EVT_TOOL, self.OnClose, id=26)
        
    #-----------------------------------------------------------------------

    def createStatusBar(self):
        self.sb = StatusBar.My_CustomStatusBar(self)
        self.SetStatusBar(self.sb)
        self.SetStatusText(u"Welcome to PyLookInside !", 0)
        
    #-----------------------------------------------------------------------

    def createTaskBarIcon(self):        
        self.tskic = TaskBarIcon.My_TaskBarIcon(self)

    #-----------------------------------------------------------------------

    def createSplitter(self):
        self.sp1 = Splitter.My_Splitter(self)
        
        self.leftpanel = wx.Panel (self.sp1,
                                   style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)
        self.rightpanel = wx.Panel (self.sp1,
                                    style=wx.BORDER_SIMPLE | wx.TAB_TRAVERSAL)

    #-----------------------------------------------------------------------
       
    def createListCtrl(self):
        self.list = ListCtrlVirtual.My_ListCtrl(self.leftpanel)        
        self.list.SetFocus()
        
    #-----------------------------------------------------------------------

    def createStaticBox(self):
        self.stbx1 = StaticBoxOne.My_StaticBox(self.rightpanel)
        self.stbx2 = StaticBoxTwo.My_StaticBox(self.rightpanel)
        self.stbx3 = StaticBoxThree.My_StaticBox(self.rightpanel)
        self.stbx4 = StaticBoxFour.My_StaticBox(self.rightpanel)
        self.stbx5 = StaticBoxFive.My_StaticBox(self.rightpanel)
        
    #-----------------------------------------------------------------------
        
    def doLayout(self):        
        listSizer = wx.BoxSizer(wx.VERTICAL)

        listSizer.Add(self.list, 1, wx.EXPAND)

        #----------

        sizer1 = wx.BoxSizer(wx.HORIZONTAL)
        sizer2 = wx.BoxSizer(wx.HORIZONTAL)
        sizer3 = wx.BoxSizer(wx.HORIZONTAL)
        sizer4 = wx.BoxSizer(wx.HORIZONTAL)
        sizer5 = wx.BoxSizer(wx.HORIZONTAL)
        
        sizer1.Add(self.stbx1, 1, wx.EXPAND | wx.ALL, 0)
        sizer2.Add(self.stbx2, 1, wx.EXPAND | wx.ALL, 0)
        sizer3.Add(self.stbx3, 1, wx.EXPAND | wx.ALL, 0)
        sizer4.Add(self.stbx4, 1, wx.EXPAND | wx.ALL, 0)
        sizer5.Add(self.stbx5, 1, wx.EXPAND | wx.ALL, 0)

        #----------
        
        topSizer = wx.BoxSizer(wx.VERTICAL)

        topSizer.Add(sizer1, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer2, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer3, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer4, 0, wx.EXPAND | wx.ALL, 3)
        topSizer.Add(sizer5, 0, wx.EXPAND | wx.ALL, 3)

        #----------
       
        self.sp1.SplitVertically(self.leftpanel, self.rightpanel)

        #----------

        self.leftpanel.SetAutoLayout(True)
        self.rightpanel.SetAutoLayout(True)

        #----------
        
        self.leftpanel.SetSizer(listSizer)
        self.rightpanel.SetSizer(topSizer)

        #----------

        topSizer.Fit(self.rightpanel)
        listSizer.Fit(self.leftpanel)

    #-----------------------------------------------------------------------      

    def OnFileOpen(self, event):

        self.fileOpen = FileDialog.My_FileDialog(self)

    #-----------------------------------------------------------------------
        
    def OnDisassemble(self, event):
        pass
    
    #-----------------------------------------------------------------------     

    def OnAbout(self, event):
        self.notebook = AboutNotebook.My_Notebook(self)

    #-----------------------------------------------------------------------   
        
    def OnMemento(self, event):
        self.memento = MementoProvider.My_Memento(self)

    #-----------------------------------------------------------------------
        
    def OnlineHelp(self, event):
        webbrowser.open_new("http://www.beaengine.org")

    #-----------------------------------------------------------------------

#def capture_screenshot(event):
        
    def OnScreenShot(self, event):
     
        #Works on Windows XP and Linux.
        event.Skip()
        rect = self.GetRect()
        if sys.platform == 'linux2':
            #On linux, GetRect() returns size of client, not size of window.
            #Compensate for this
            client_x, client_y = self.frame.ClientToScreen((0, 0))
            border_width = client_x - rect.x
            title_bar_height = client_y - rect.y
            #If the window has a menu bar, remove it from the title bar height.
            if self.frame.GetMenuBar():
                title_bar_height /= 2
            rect.width += (border_width * 2)
            rect.height += title_bar_height + border_width
            self.frame.Raise()
            viewer_dc = wx.ScreenDC()
            bitmap = wx.EmptyBitmap(rect.width, rect.height)
            memory_dc = wx.MemoryDC()
            memory_dc.SelectObject(bitmap)
            memory_dc.Blit(0, 0, rect.width, rect.height, viewer_dc, rect.x, rect.y)
            memory_dc.SelectObject(wx.NullBitmap)
            image = bitmap.ConvertToImage()
            image.SaveFile('screenshot.png', wx.BITMAP_TYPE_PNG)

    #-----------------------------------------------------------------------
        
    def OnPass(self, event):
        pass
    
    #-----------------------------------------------------------------------

    def OnRoll(self, event):
        if self.isRolled == 1:
            return
        self.isRolled = 1

        self.pos1 = self.GetPosition()
        self.size1 = self.GetSize()
        
        if wx.Platform == "__WXMAC__":
            self.SetSize((-1, 22))
           
        elif wx.Platform == "__WXGTK__":
            self.SetSize((-1, 0))
            
        else:
            self.SetSize((-1, 0))


    def OnUnRoll(self, event):
        self.isRolled = 0

        self.pos2 = self.GetPosition()
        self.size2 = self.GetSize()
        
        if wx.Platform == "__WXMAC__":
            self.SetSize(self.size1)
            
        elif wx.Platform == "__WXGTK__":
            self.SetSize(self.size1)
            
        else:
            self.SetSize(self.size1)
     
    #-----------------------------------------------------------------------
        
    def OnClose(self, event):
        # Triggers wx.EVT_CLOSE event and hence onCloseWindow()
        self.Close(True)

        
    def OnCloseWindow(self, event):
        # Dialog to verify exit 
        dlg = wx.MessageDialog(self,
                               message=u"Do you really want to close this application ?",
                               caption=u"Confirm Exit",
                               style=wx.YES_NO | wx.ICON_QUESTION)

        if dlg.ShowModal() == wx.ID_YES:
            if self.tskic is not None:
                self.tskic.Destroy()
                
            self.sb.timer.Stop()
            del self.sb.timer
            self.Destroy()

        dlg.Destroy()

#---------------------------------------------------------------------------
      
class My_App(wx.App):
    def OnInit(self):
        
        # Create and show the splash screen.  It will then create 
        # and show the main frame when it is time to do so
        wx.SystemOptions.SetOptionInt("mac.window-plain-transition", 1)

        # Normally when using a SplashScreen you would create it, show
        # it and then continue on with the applicaiton's
        # initialization, finally creating and showing the main
        # application window(s).  In this case we have nothing else to
        # do so we'll delay showing the main frame until later (see
        # ShowMain above) so the users can see the SplashScreen effect        
        self.splash = SplashScreen.My_SplashScreen()
        self.splash.Show()

        return True   
        
#---------------------------------------------------------------------------

def main():
    app = My_App(redirect=False)
    app.MainLoop()

#----------------------------------------------------------------------------

if __name__ == '__main__':
    __name__ = 'Main'
    main()


