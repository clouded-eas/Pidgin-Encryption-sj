;NSIS Script For Pidgin-Encryption Plugin (MUI version)
; Based on installers by Mike Campell and Daniel Atallah, and on the Pidgin installer by
; Herman Bloggs.  Many thanks!
; probably will not work with older versions of NSIS
; Requires NSIS 2.0 or greater

Name "Pidgin-Encryption ${PIDGIN-ENCRYPTION_VERSION}"
!define MY_NAME Name

; Registry keys:
!define PIDGIN_ENCRYPTION_REG_KEY         "SOFTWARE\pidgin-encryption"
!define PIDGIN_ENCRYPTION_UNINSTALL_KEY   "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\pidgin-encryption"
!define PIDGIN_ENCRYPTION_UNINST_EXE      "pidgin-encryption-uninst.exe"

!define ALL_LINGUAS "bg cs da de es fr hu it ja lt nl nn pl pt_BR pt_PT ro ru sl sv ta tr uk zh_CN zh_TW"

!include "MUI.nsh"

;Do A CRC Check
CRCCheck On

;Output File Name
OutFile "pidgin-encryption-${PIDGIN-ENCRYPTION_VERSION}.exe"

ShowInstDetails show
ShowUnInstDetails show
SetCompressor lzma

; Translations


; Modern UI Configuration

!define MUI_ICON .\nsis\install.ico
!define MUI_UNICON .\nsis\install.ico
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "nsis\header.bmp"

; Pidgin Plugin installer helper stuff
;!addincludedir "..\..\src\win32\nsis"
;!include "pidgin-plugin.nsh"

; Pages
; !insertmacro MUI_LANGDLL_DISPLAY

!define MUI_WELCOMEPAGE_TITLE $(WELCOME_TITLE)
!define MUI_WELCOMEPAGE_TEXT $(WELCOME_TEXT)
!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_LICENSE  "./COPYING"

!define MUI_DIRECTORYPAGE_TEXT_TOP $(DIR_SUBTITLE)
!define MUI_DIRECTORYPAGE_TEXT_DESTINATION $(DIR_INNERTEXT)
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_TITLE $(FINISH_TITLE)
!define MUI_FINISHPAGE_TEXT $(FINISH_TEXT)
!insertmacro MUI_PAGE_FINISH

; MUI Config

!define MUI_CUSTOMFUNCTION_GUIINIT encrypt_checkPidginVersion
!define MUI_ABORTWARNING
!define MUI_UNINSTALLER
!define MUI_PROGRESSBAR smooth
!define MUI_INSTALLCOLORS /windows
;  !define MUI_FINISHPAGE_TEXT $(G-E_INSTALL_FINISHED)
;  !define MUI_FINISHPAGE_NOAUTOCLOSE
;!define MUI_TEXT_WELCOME_INFO_TEXT $(WELCOME_TEXT)
;!define MUI_TEXT_DIRECTORY_SUBTITLE $(DIR_SUBTITLE)
;!define MUI_INNERTEXT_DIRECTORY_TOP $(DIR_INNERTEXT)


;; Here in alphabetical order in native language
;; i.e. Danish, Deutsch, Espanol, Francais... , not Danish, French, German, Spanish...
;; English first as a default

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Bulgarian"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "Danish"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Hungarian"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Lithuanian"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "Norwegian"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Slovenian"
!insertmacro MUI_LANGUAGE "Turkish"
!insertmacro MUI_LANGUAGE "Ukrainian"

!include "nsis\translations\english.nsh"
!include "nsis\translations\czech.nsh"
!include "nsis\translations\danish.nsh"
!include "nsis\translations\trad-chinese.nsh"
!include "nsis\translations\german.nsh"
!include "nsis\translations\spanish.nsh"
!include "nsis\translations\french.nsh"
!include "nsis\translations\hungarian.nsh"
!include "nsis\translations\italian.nsh"
!include "nsis\translations\japanese.nsh"
!include "nsis\translations\lithuanian.nsh"
!include "nsis\translations\dutch.nsh"
!include "nsis\translations\norwegian.nsh"
!include "nsis\translations\polish.nsh"
!include "nsis\translations\portugueseBR.nsh"
!include "nsis\translations\romanian.nsh"
!include "nsis\translations\russian.nsh"
!include "nsis\translations\slovenian.nsh"
!include "nsis\translations\turkish.nsh"
!include "nsis\translations\ukrainian.nsh"



!define MUI_LICENSEPAGE_RADIOBUTTONS


;The Default Installation Directory
InstallDir "$PROGRAMFILES\pidgin"
InstallDirRegKey HKLM SOFTWARE\pidgin ""

Section -SecUninstallOldPlugin
  ; Check install rights..
  Call CheckUserInstallRights
  Pop $R0

  StrCmp $R0 "HKLM" rights_hklm
  StrCmp $R0 "HKCU" rights_hkcu done

  rights_hkcu:
      ReadRegStr $R1 HKCU ${PIDGIN_ENCRYPTION_REG_KEY} ""
      ReadRegStr $R2 HKCU ${PIDGIN_ENCRYPTION_REG_KEY} "Version"
      ReadRegStr $R3 HKCU "${PIDGIN_ENCRYPTION_UNINSTALL_KEY}" "UninstallString"
      Goto try_uninstall

  rights_hklm:
      ReadRegStr $R1 HKLM ${PIDGIN_ENCRYPTION_REG_KEY} ""
      ReadRegStr $R2 HKLM ${PIDGIN_ENCRYPTION_REG_KEY} "Version"
      ReadRegStr $R3 HKLM "${PIDGIN_ENCRYPTION_UNINSTALL_KEY}" "UninstallString"

  ; If previous version exists .. remove
  try_uninstall:
    StrCmp $R1 "" done
      StrCmp $R2 "" uninstall_problem
        IfFileExists $R3 0 uninstall_problem
          ; Have uninstall string.. go ahead and uninstall.
          SetOverwrite on
          ; Need to copy uninstaller outside of the install dir
          ClearErrors
          CopyFiles /SILENT $R3 "$TEMP\${PIDGIN_ENCRYPTION_UNINST_EXE}"
          SetOverwrite off
          IfErrors uninstall_problem
            ; Ready to uninstall..
            ClearErrors
            ExecWait '"$TEMP\${PIDGIN_ENCRYPTION_UNINST_EXE}" /S _?=$R1'
            IfErrors exec_error
              Delete "$TEMP\${PIDGIN_ENCRYPTION_UNINST_EXE}"
              Goto done

            exec_error:
              Delete "$TEMP\${PIDGIN_ENCRYPTION_UNINST_EXE}"
              Goto uninstall_problem

        uninstall_problem:
            ; Just delete the plugin and uninstaller, and remove Registry key
             MessageBox MB_YESNO $(PIDGIN_ENCRYPTION_PROMPT_WIPEOUT) IDYES do_wipeout IDNO cancel_install
          cancel_install:
            Quit

          do_wipeout:
            StrCmp $R0 "HKLM" del_lm_reg del_cu_reg
            del_cu_reg:
              DeleteRegKey HKCU ${PIDGIN_ENCRYPTION_REG_KEY}
              Goto uninstall_prob_cont
            del_lm_reg:
              DeleteRegKey HKLM ${PIDGIN_ENCRYPTION_REG_KEY}

            uninstall_prob_cont:
              Delete "$R1\plugins\encrypt.dll"
              Delete "$R3"

  done:

SectionEnd


Section "Install"

  Call CheckUserInstallRights
  Pop $R0

  StrCmp $R0 "NONE" instrights_none
  StrCmp $R0 "HKLM" instrights_hklm instrights_hkcu

  instrights_hklm:
    ; Write the version registry keys:
    WriteRegStr HKLM ${PIDGIN_ENCRYPTION_REG_KEY} "" "$INSTDIR"
    WriteRegStr HKLM ${PIDGIN_ENCRYPTION_REG_KEY} "Version" "${PIDGIN-ENCRYPTION_VERSION}"

    ; Write the uninstall keys for Windows
    WriteRegStr HKLM ${PIDGIN_ENCRYPTION_UNINSTALL_KEY} "DisplayName" "$(PIDGIN_ENCRYPTION_UNINSTALL_DESC)"
    WriteRegStr HKLM ${PIDGIN_ENCRYPTION_UNINSTALL_KEY} "UninstallString" "$INSTDIR\${PIDGIN_ENCRYPTION_UNINST_EXE}"
    SetShellVarContext "all"
    Goto install_files

  instrights_hkcu:
    ; Write the version registry keys:
    WriteRegStr HKCU ${PIDGIN_ENCRYPTION_REG_KEY} "" "$INSTDIR"
    WriteRegStr HKCU ${PIDGIN_ENCRYPTION_REG_KEY} "Version" "${PIDGIN-ENCRYPTION_VERSION}"

    ; Write the uninstall keys for Windows
    WriteRegStr HKCU ${PIDGIN_ENCRYPTION_UNINSTALL_KEY} "DisplayName" "$(PIDGIN_ENCRYPTION_UNINSTALL_DESC)"
    WriteRegStr HKCU ${PIDGIN_ENCRYPTION_UNINSTALL_KEY} "UninstallString" "$INSTDIR\${PIDGIN_ENCRYPTION_UNINST_EXE}"
    Goto install_files
  
  instrights_none:
    ; No registry keys for us...
    
  install_files:
    SetOutPath $INSTDIR
    SetCompress Auto
    SetOverwrite on
    File /r ".\win32-install-dir\*.*"

    StrCmp $R0 "NONE" done
    CreateShortCut "$SMPROGRAMS\Pidgin\Pidgin-Encryption Uninstall.lnk" "$INSTDIR\${PIDGIN_ENCRYPTION_UNINST_EXE}"
    WriteUninstaller "$INSTDIR\${PIDGIN_ENCRYPTION_UNINST_EXE}"
    SetOverWrite off

  done:
SectionEnd

Section Uninstall
  Call un.CheckUserInstallRights
  Pop $R0
  StrCmp $R0 "NONE" no_rights
  StrCmp $R0 "HKCU" try_hkcu try_hklm

  try_hkcu:
    ReadRegStr $R0 HKCU ${PIDGIN_ENCRYPTION_REG_KEY} ""
    StrCmp $R0 $INSTDIR 0 cant_uninstall
      ; HKCU install path matches our INSTDIR.. so uninstall
      DeleteRegKey HKCU ${PIDGIN_ENCRYPTION_REG_KEY}
      DeleteRegKey HKCU "${PIDGIN_ENCRYPTION_UNINSTALL_KEY}"
      Goto cont_uninstall

  try_hklm:
    ReadRegStr $R0 HKLM ${PIDGIN_ENCRYPTION_REG_KEY} ""
    StrCmp $R0 $INSTDIR 0 try_hkcu
      ; HKLM install path matches our INSTDIR.. so uninstall
      DeleteRegKey HKLM ${PIDGIN_ENCRYPTION_REG_KEY}
      DeleteRegKey HKLM "${PIDGIN_ENCRYPTION_UNINSTALL_KEY}"
      ; Sets start menu and desktop scope to all users..
      SetShellVarContext "all"

  cont_uninstall:
    ; plugin 
    Delete "$INSTDIR\plugins\encrypt.dll"

     ; all locales
     Push $R0 ;save old values
     Push $R1
     Push $R2
     Push "${ALL_LINGUAS}"
     Pop $R0 ;initialize input array
     alllinguas:
     StrLen $R1 $R0 ;length of input array
     IntCmp $R1 0 alldone
     IntOp $R1 $R1 + 1
     uptodelimiter:
         IntOp $R1 $R1 - 1
         IntCmp $R1 0 fullof fullof
         StrCpy $R2 $R0 1 -$R1
         StrCmp $R2 "" fullof
         StrCmp $R2 " " partof
     Goto uptodelimiter
     partof:
         StrCpy $R2 $R0 -$R1
         IntOp $R1 $R1 - 1
         StrCpy $R0 $R0 "" -$R1
         Goto dodelwork
     fullof:
         StrCpy $R2 $R0
         StrCpy $R0 ""
     dodelwork:
     StrCpy $R1 "$INSTDIR\locale"
     Push $R1
     StrCpy $R1 "$R1\$R2"
     Push $R1
     StrCpy $R1 "$R1\LC_MESSAGES"
     Delete "$R1\pidgin-encryption.mo"
     RMDir $R1
     Pop $R1
     RMDir $R1
     Pop $R1
     RMDir $R1
     Goto alllinguas
     alldone:
     Pop $R2 ;restore old values
     Pop $R1
     Pop $R0

    ; uninstaller shortcut
    Delete "$SMPROGRAMS\Pidgin\Pidgin-Encryption Uninstall.lnk"

    ; uninstaller
    Delete "$INSTDIR\${PIDGIN_ENCRYPTION_UNINST_EXE}"
    Delete "$INSTDIR\pixmaps\pidgin-encryption\*.png"
    RMDir "$INSTDIR\pixmaps\pidgin-encryption"

    ; try to delete the Pidgin directories, in case it has already uninstalled
    RMDir "$INSTDIR\plugins"
    RMDIR "$INSTDIR\locale"
    RMDir "$INSTDIR"
    RMDir "$SMPROGRAMS\Pidgin"

    Goto done

  cant_uninstall:
    MessageBox MB_OK $(un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1) IDOK
    Quit

  no_rights:
    MessageBox MB_OK $(un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2) IDOK
    Quit

  done:
SectionEnd

Function .onVerifyInstDir
  IfFileExists $INSTDIR\pidgin.exe Good1
    Abort
  Good1:
FunctionEnd

Function encrypt_checkPidginVersion
;  Push $R0
;  Push ${PIDGIN_VERSION}
;  Call CheckPidginVersion
;  Pop $R0
;
;  StrCmp $R0 ${PIDGIN_VERSION_OK} encrypt_checkPidginVersion_OK
;
;    StrCmp $R0 ${PIDGIN_VERSION_INCOMPATIBLE} +1 +6
;    Call GetPidginVersion
;    IfErrors +3
;    Pop $R0
;    MessageBox MB_OK|MB_ICONSTOP "$(BAD_PIDGIN_VERSION_1) $R0 $(BAD_PIDGIN_VERSION_2)"
;    goto +2
;    MessageBox MB_OK|MB_ICONSTOP "$(UNKNOWN_PIDGIN_VERSION)"
;    Quit
;
;  encrypt_checkPidginVersion_OK:
;  Pop $R0

FunctionEnd

Function CheckUserInstallRights
        ClearErrors
        UserInfo::GetName
        IfErrors Win9x
        Pop $0
        UserInfo::GetAccountType
        Pop $1

        StrCmp $1 "Admin" 0 +3
                StrCpy $1 "HKLM"
                Goto done
        StrCmp $1 "Power" 0 +3
                StrCpy $1 "HKLM"
                Goto done
        StrCmp $1 "User" 0 +3
                StrCpy $1 "HKCU"
                Goto done
        StrCmp $1 "Guest" 0 +3
                StrCpy $1 "NONE"
                Goto done
        ; Unknown error
        StrCpy $1 "NONE"
        Goto done

        Win9x:
                StrCpy $1 "HKLM"

        done:
        Push $1
FunctionEnd

Function un.CheckUserInstallRights
        ClearErrors
        UserInfo::GetName
        IfErrors Win9x
        Pop $0
        UserInfo::GetAccountType
        Pop $1
        StrCmp $1 "Admin" 0 +3
                StrCpy $1 "HKLM"
                Goto done
        StrCmp $1 "Power" 0 +3
                StrCpy $1 "HKLM"
                Goto done
        StrCmp $1 "User" 0 +3
                StrCpy $1 "HKCU"
                Goto done
        StrCmp $1 "Guest" 0 +3
                StrCpy $1 "NONE"
                Goto done
        ; Unknown error
        StrCpy $1 "NONE"
        Goto done

        Win9x:
                StrCpy $1 "HKLM"

        done:
        Push $1
FunctionEnd

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd
