cmake_minimum_required(VERSION 3.13)

project(3DS-Card-Collection)

set(SOURCE_FILES
  src/table/tableEngine.cpp
  src/table/table.cpp
  src/table/client.cpp
  src/table/host.cpp
  src/main.cpp
)

set(CARD_IMAGES
  cards/card_back.png
)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(src)
link_libraries(SDL3::SDL3 ctru)

add_executable(card-collection ${SOURCE_FILES})

# TODO - images
dkp_add_asset_target(romfs assets)
dkp_track_assets(romfs FILES ${CARD_IMAGES})

ctr_generate_smdh(3DS-Card-Collection.smdh
  NAME "Card Collection"
  AUTHOR "Daniel Budke"
  DESCRIPTION "Multiplayer card games for the 3DS"
)

ctr_create_3dsx(card-collection
  SMDH 3DS-Card-Collection.smdh
  ROMFS romfs
)
