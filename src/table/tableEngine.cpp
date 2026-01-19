/*
    Host-side table handling and communication abstraction
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

#include "tableEngine.hpp"
#include <3ds.h>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

using namespace Table;

Engine::Engine() { udsInit(0x3000, NULL); }

Engine::~Engine() {
  if (currentTable != nullptr) {
    delete currentTable;
  }
  udsExit();
}

Engine::ScanResults Engine::scanForTables() {
  ScanResults results;
  Result ret;

  udsNetworkScanInfo *networks{nullptr};
  size_t numNetworks{0};

  // i don't know why libctru makes you do this, there's probably a reason way
  // above my pay grade
  const size_t tempBufSize = 0x4000;
  auto tempBuf = std::make_unique<u8[]>(tempBufSize);
  udsScanBeacons(tempBuf.get(), tempBufSize, &networks, &numNetworks,
                 wlancommid, 0, NULL, false);

  for (int i{0}; i < numNetworks; i++) {
    udsNetworkScanInfo &network = networks[i];
    udsNodeInfo &host = network.nodes[0];
    // parse table data
    if (!udsCheckNodeInfoInitialized(&host))
      continue;

    // according to UDS, hostname will never be above 10 chars w/null terminator
    auto hostnameBuf = std::make_unique<char[]>(11);
    ret = udsGetNodeInfoUsername(&host, hostnameBuf.get());
    auto hostname = std::string(hostnameBuf.get());

    // get appdata from beacon, verify
    // this code should be pretty safe, probably isn't. please yell at me.
    size_t appdataSize;
    auto networkAppdataBuf = std::make_unique<u8[]>(sizeof(AppData));
    ret = udsGetNetworkStructApplicationData(&(network.network),
                                             networkAppdataBuf.get(),
                                             sizeof(AppData), &appdataSize);
    if (!AppData::isValid(networkAppdataBuf.get(), appdataSize))
      continue;

    auto networkAppdata = AppData(networkAppdataBuf.release());
    if (networkAppdata.version > version) {
      results.hasNewerVersions = true;
      continue;
    }

    results.addTable(hostname, &(network.network));
  }

  return results;
}

bool Engine::connectToTable(const ScanResults::DiscoveredTable &table) {
  return false;
}
