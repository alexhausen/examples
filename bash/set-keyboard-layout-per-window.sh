#!/bin/bash
# Author: Serg Kolo
# Date: August 4, 2015
# Description: This script forces assigned input languages
#              for specific windows
# Version:2

# Use this part to set programs and their respective languages
# PROG_CLASS or a running window can be found with the
# wmctrl -lx command
# If you want to add another program to the list, 
# follow the template PROG_CLASS_num=window.Class
# and bellow that $LANGnum=num

#http://askubuntu.com/questions/655628/assign-default-keyboard-language-per-application

#"0" = EN-US, "1" = EN-US intl
#[('xkb', 'us'), ('xkb', 'us+intl'), ('xkb', 'br')]

P0=("gedit.Gedit" "0")
P1=("sakura.Sakura" "0")
P2=("Eclipse.Eclipse" "0")
P3=("Navigator.Firefox" "1")
P4=("rhythmbox.Rhythmbox" "1")
P5=("Mail.Thunderbird" "1")
P6=("Msgcompose.Thunderbird", "1")
P7=("skype.Skype" "1")
P8=("rocket.chat.Rocket.Chat" "1")

PROGS=(P0[@] P1[@] P2[@] P3[@] P4[@] P5[@] P6[@] P7[@] P8[@])
PROGS_COUNT=${#PROGS[@]}

while [ 1 ];do
  ACTIVE_WINDOW=$(xdotool getactivewindow 2>/dev/null)
  if [ $? -eq 1 ]; then
    #echo "error"
    sleep 1
    continue
  fi
  CURRENT_CLASS=$(wmctrl -lx | awk -v search=$(printf %x $ACTIVE_WINDOW) '{ if($1~search) print $3 }' )
  CURRENT_LAYOUT=$(gsettings get org.gnome.desktop.input-sources current| awk '{print $2}')
  #echo "current window class and keyboard layout $CURRENT_CLASS:$CURRENT_LAYOUT"
  for ((i=0; i<$PROGS_COUNT; i++))
  do
    CLASS=${!PROGS[i]:0:1}
    LAYOUT=${!PROGS[i]:1:1}
    if [ "$CURRENT_CLASS" == "$CLASS" ];then
      #echo "$CLASS:$LAYOUT"
      if [ $CURRENT_LAYOUT -ne $LAYOUT ];then
        #echo "set keyboard layout $LAYOUT on $CLASS"
        gsettings set org.gnome.desktop.input-sources current $LAYOUT
      fi
    fi
  done
  sleep 1
done
