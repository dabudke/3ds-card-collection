/*
    Code for hosting a table/spawning a local multiplayer network
    Copyright (C) 2026  Daniel Budke

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https: //www.gnu.org/licenses/>.
*/
#include <cstring>
#include <3ds.h>
#include "table.hpp"
#include "tableEngine.hpp"

namespace Table
{
  HostedTable::HostedTable()
  {
    Engine &tableEngine = Engine::getInstance();
    udsGenerateDefaultNetworkStruct(&networkStruct, Engine::wlancommid, 0, UDS_MAXNODES);

    Result ret = udsCreateNetwork(&networkStruct, Engine::passphrase, strlen(Engine::passphrase) + 1, &bindContext, 1, UDS_DEFAULT_RECVBUFSIZE);

    ret = udsSetApplicationData(tableEngine.getAppdata(), sizeof(Engine::AppData));

    udsWaitConnectionStatusEvent(false, true);
    udsGetConnectionStatus(&connectionStatus);
  }

  HostedTable::~HostedTable()
  {
    udsDestroyNetwork();
  }
}
