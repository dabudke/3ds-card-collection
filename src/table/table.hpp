/*
    Abstraction layer of core 3DS UDS operations
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
#include <memory>
#include <3ds.h>

namespace Table
{
  /**
   * @brief Contract for both host and client table form factors (UDS and in future network)
   *
   */
  class BaseTable
  {
    friend class Engine;

  protected:
    BaseTable();
    ~BaseTable();
    udsBindContext bindContext;
    std::unique_ptr<u8[]> tempBuf;
    udsConnectionStatus connectionStatus;

  public:
    udsConnectionStatus &getConnectionStatus();
    void broadcastData();
    void pullData();
  };

  class HostedTable : public BaseTable
  {
  private:
    udsNetworkStruct networkStruct;

  public:
    HostedTable();
    ~HostedTable();
  };
  class ClientTable : public BaseTable
  {
  private:
    ClientTable(udsNetworkStruct *network);

  public:
    ~ClientTable();
  };
}
