# -*- coding: utf8 -*-

# Import des modules

import wx                    # Ce module utilise le nouvel espace de nom wx.
import sys
import os
import time
import PyLookInside
import VersionInfos
import wx.animate as ani
#import images

#---------------------------------------------------------------------------

class BoutonAnime(wx.Window):
    """ Crée la classe de l'objet animé. """
    def __init__(self, parent, image):
        wx.Window.__init__(self, parent, -1, style=wx.BORDER_NONE)
        # self.SetBackgroundColour(wx.WHITE)
        self.image = image
        animation = ani.Animation(self.image)
        self.ctrl = ani.AnimationCtrl(self, -1, animation)
        # self.ctrl.SetUseWindowBackgroundColour(True)
        self.ctrl.Play()

        # Lie un événement de taille au gestionnaire d'événements            
        self.Bind(wx.EVT_SIZE, self.OnSize)

        
    def OnSize(self, event):
        # Récupére largeur et hauteur de l'image
        w, h = self.ctrl.GetSizeTuple()
        taille = wx.Size(w, h)
        taille = wx.Size(w+1, h+1)
        self.SetSize(taille)
        self.SetPosition((436, 3))
        self.ctrl.CentreOnParent()
        
#---------------------------------------------------------------------------

class My_SplashScreen(wx.Frame):
    """ Crée la classe du SplashScreen. """
    def __init__(self, tempo = 2):
        self.tempo = tempo
        
        wx.Frame.__init__(self, None, -1,
                          style = wx.FRAME_SHAPED | wx.SIMPLE_BORDER |
                          wx.STAY_ON_TOP | wx.FRAME_NO_TASKBAR)        

        self.hasShaped = False
        
        # Charge l'image du SplashScreen      
        # bmp = images.SplashScreen.GetBitmap()
        self.bmp = wx.Bitmap("Bitmaps/splashScreen.png", wx.BITMAP_TYPE_PNG)

        # Charge l'image animée
        self.bouton = BoutonAnime(self, "Bitmaps/loading.ani")
        
        # Récupère la taille du SplashScreen
        self.SetClientSize((self.bmp.GetWidth(), self.bmp.GetHeight()))

        # Crée une wx.ClientDC
        dc = wx.ClientDC(self)
        dc.DrawBitmap(self.bmp, 0, 0, True)
        self.SetWindowsShape()

        # Crée un Timer (ferme la fenêtre au bout du temps tempo)
        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.TimeOut)
        
        # Affiche la frame principale après 2000 ms
        self.fc = wx.FutureCall(1500, self.ShowMain)
        
        # Lie des événements au gestionnaire d'événements        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_WINDOW_CREATE, self.SetWindowsShape)
        self.Bind(wx.EVT_CLOSE, self.OnClose)

        # Centre la fenêtre à l'écran
        self.CentreOnScreen(wx.BOTH)
        
    #-----------------------------------------------------------------------
    
    def OnClose(self, event):
        # Make sure the default handler runs too so
        # this window gets destroyed
        event.Skip()
        self.Hide()
        
        # If the timer is still running then go
        # ahead and show the main frame now
        if self.fc.IsRunning():
            self.fc.Stop()
            self.ShowMain()

    #-----------------------------------------------------------------------
            
    def TimeOut(self, event):
        # Fonction appelée lors du Timeout du Timer
        self.Close()

    #-----------------------------------------------------------------------
        
    def SetWindowsShape(self, event=None):
        region = wx.RegionFromBitmap(self.bmp)
        self.hasShaped = self.SetShape(region)

    #-----------------------------------------------------------------------
        
    def OnPaint(self, event):
        # Dessine sur l'image
        dc = wx.PaintDC(self)
        dc.DrawBitmap(self.bmp, 0, 0, True)

        if self.tempo>0:
            self.timer.Start(self.tempo * 1000, True)

        #-------------------------------------------------------------------
            
        # Paramètre le style de police de caractères
        # Récupère taille et police de l'OS
        fontSize = self.GetFont().GetPointSize()

        # wx.Font(pointSize, family, style, weight, underline, faceName)         
        if wx.Platform == "__WXMAC__":
            self.normalBoldFont = wx.Font(fontSize-3, wx.DEFAULT, wx.NORMAL, wx.BOLD, False, "")
            self.normalFont = wx.Font(fontSize-3, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
            
        elif wx.Platform == "__WXGTK__":
            self.normalBoldFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.BOLD, False, "")
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
              
        else:
            self.normalBoldFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.BOLD, False, "")
            self.normalFont = wx.Font(fontSize+0, wx.DEFAULT, wx.NORMAL, wx.NORMAL, False, "")
       
        dc.SetFont(self.normalFont)
        dc.SetFont(self.normalBoldFont)

        #-------------------------------------------------------------------

        # Affiche les divers textes d'info
        
        dc.SetTextForeground(wx.BLACK)
        dc.SetFont(self.normalBoldFont)        

        dc.DrawText(u"%s" % VersionInfos.LICENSE1_STRING, 50, 160)
        dc.SetFont(self.normalFont)
        dc.DrawText(u"%s" % VersionInfos.COMMENT_STRING, 50, 185)
        dc.DrawText(u"%s" % VersionInfos.LICENSE3_STRING, 50, 200)
        dc.DrawText(u"%s" % VersionInfos.COPYRIGHT_STRING, 50, 215)
        dc.DrawText(u"%s" % VersionInfos.LICENSE2_STRING, 50, 230)
        dc.DrawText(u"PyLookInside est issu de Python "
                    + sys.version.split()[0] + "," +
                    " wxPython "
                    + wx.VERSION_STRING + u" unicode" +
                    u" et wxWindows.", 50, 245)
        dc.DrawText(u"%s" % VersionInfos.OS_STRING
                    + sys.platform + u"/"
                    + os.name + "." , 50, 260)
        
    #-----------------------------------------------------------------------
        
    def ShowMain(self):
        self.frame = PyLookInside.My_Frame(None, -1)
    
        # Ajoute une icône à la MainFrame
        # frameicon = images.Icon_App.GetIcon()
        frameicon = wx.Icon("Icons/icon_App.ico", wx.BITMAP_TYPE_ICO)
        self.frame.SetIcon(frameicon)
       
        self.frame.Show(True)
        self.ctrl.Stop()            # ajout à vérifier sur mac
        
        if self.fc.IsRunning():
            self.Raise()



