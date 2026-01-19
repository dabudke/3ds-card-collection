/*
    Network synchronization engine for both UDS and internet games
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

#pragma once
#include "table.hpp"
#include <3ds.h>
#include <cstring>
#include <string>
#include <vector>

namespace Table {
// results of one table scan procedure

class Engine {
  friend class HostedTable;
  friend class ClientTable;

public:
  struct ScanResults {
    friend Engine;

  public:
    struct DiscoveredTable {
    private:
      DiscoveredTable(std::string hostname, udsNetworkStruct *network)
          : hostname(hostname), network(network) {};
      const udsNetworkStruct *network;
      friend ScanResults;
      friend Engine;

    public:
      const std::string hostname;
    };

    bool hasNewerVersions{false};
    std::vector<DiscoveredTable> tables;

  private:
    inline void addTable(std::string hostname, udsNetworkStruct *network) {
      tables.push_back(DiscoveredTable(hostname, network));
    }
  };

private:
  // broadcasted appdata for tables - game verification ID and
  struct AppData {
    AppData(u8 *buffer);
    AppData(const char id[4], u16 version) : version(version) {
      strncpy(this->id, id, 4);
    }
    // TODO - data validation
    static bool isValid(const void *other, size_t size) {
      if (size != sizeof(AppData))
        return false;
      return true;
    }
    char id[4];
    u16 version; // change this if a breaking change will occur
  };
  static constexpr char id[4]{'C', 'A', 'R', 'D'};
  static const u16 version = 0x0001;
  inline static AppData *getAppdata() {
    static AppData appdata(id, version);
    return &appdata;
  }

  std::unique_ptr<udsNetworkScanInfo[]> networks;

  ScanResults previousTableScan;

  BaseTable *currentTable{nullptr};

  Engine();
  ~Engine();

  // unique ID
  static const u32 wlancommid = 873550404;
  // unique passphrase, type doesn't matter
  static constexpr char passphrase[42] =
      "passphrase alkfsjlkadjfklajdsklfjalkdfjkl";
  static constexpr int passphraseLen = 42;

public:
  static Engine &getInstance() {
    static Engine instance;
    return instance;
  }
  // copy constructor
  Engine(const Engine &) = delete;
  // assignment operator
  Engine &operator=(const Engine &) = delete;

  // Initiate a scan for tables (call from another thread to ensure safety)
  ScanResults scanForTables();

  bool connectToTable(const ScanResults::DiscoveredTable &table);

  void hostTable();
};
} // namespace Table
