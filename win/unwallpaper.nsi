; Nullsoft Scriptable Install System
; http://nsis.sourceforge.net/
;
; Generate exe:
;     makensis unwallpaper.nsi

OutFile "unwallpaper-0.1.0-installer.exe"

InstallDir $PROGRAMFILES32\Unwallpaper

;====================== Install ======================
Section

SetOutPath $INSTDIR

File unwallpaper.exe

; DLL
File *.dll

; Translations
File /r translations

WriteUninstaller $INSTDIR\uninstaller.exe

; Start menu shortcut
createShortCut "$SMPROGRAMS\Unwallpaper.lnk" "$INSTDIR\unwallpaper.exe"

; Desktop shortcut
createShortCut "$DESKTOP\Unwallpaper.lnk" "$INSTDIR\unwallpaper.exe"

SectionEnd

;===================== Uninstall =====================

; create a section to define what the uninstaller does.
; the section will always be named "Uninstall"
Section "Uninstall"

; Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

; Application
Delete $INSTDIR\unwallpaper.exe

; DLL
Delete $INSTDIR\*.dll

; Translations
Delete $INSTDIR\translations\*.qm

; Translations folder
RMDir $INSTDIR\translations

; Installation folder
RMDir $INSTDIR

; Start menu shortcut
Delete "$SMPROGRAMS\Unwallpaper.lnk"

; Desktop shortcut
Delete "$DESKTOP\Unwallpaper.lnk"

SectionEnd
