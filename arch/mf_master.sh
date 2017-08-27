#!/usr/bin/env bash
#-----------------------------------------------------------------------------
#
# This file is part of Magic Fontain.
#
# Magic Fontain is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Magic Fontain is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Magic Fontain.  If not, see <http://www.gnu.org/licenses/>.
#
#-----------------------------------------------------------------------------
# Author: ZeroDot1 https://github.com/ZeroDot1
# Contact: zerodot1@bk.ru
# Author Website: http://basic1.moy.su/
# Version: 1.0
# Date Time: 25.08.2017 04:19
# Credits: Thanks to Colin Duquesnoy https://github.com/ColinDuquesnoy
#-----------------------------------------------------------------------------
clear
tput setaf 2
echo '##############################################################################'
echo '# Script to beta test Magic Fontain with Archlinux/AntergOS/Manjaro          #'
echo '# ************************************************************************** #'
echo '# https://github.com/Aztorius/magicfountain/tree/master                      #'
echo '##############################################################################'
sleep 2s
read -rsp $'Delete old Magic Fontain BETA build [$HOME/magicfountain-master]. Press any key or wait 5 seconds to continue...\n' -n 1 -t 5;
rm -rf magicfountain-master
read -rsp $'Magic Fontain Testbuild for Arch Linux. This action can take a few moments to complete. Press any key or wait 5 seconds to continue...\n' -n 1 -t 5;
echo 'Create Working Folder [./magicfountain-master]'
mkdir magicfountain-master && pushd magicfountain-master
echo 'Download [Aztorius/magicfountain/archive/master.zip] . . . . .'
tput sgr0
wget --verbose --referer=https://github.com/ -t 20 --no-check-certificate https://github.com/Aztorius/magicfountain/archive/master.zip
tput setaf 2
echo 'Unzip [develop.zip to $HOME/magicfountain-dev/magicfountain-dev] and Make [This action can take a few moments to complete]'
unzip master.zip
pushd magicfountain-master
echo 'Compile . . . .'
sleep 1s
tput sgr0
qmake-qt5 PREFIX='/usr' LIBDIR='/usr/lib' magicfountain.pro
make
tput setaf 2
popd
popd
echo 'Run Magic Fontain . . . have fun!'
echo 'If you find a bug while testing Magic Fontain, please report it.'
echo 'https://github.com/Aztorius/magicfountain/issues'
sleep 2s
magicfountain-master/magicfountain-master/magicfountain
