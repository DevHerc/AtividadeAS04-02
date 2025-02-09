# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico CACHE STRING "Board type")

# Defina a versão mínima do CMake
cmake_minimum_required(VERSION 3.13)

# Defina o nome do projeto
project(Microcontroller_Project)

# Defina o caminho para o SDK do Raspberry Pi Pico
set(PICO_SDK_PATH "C:/Users/HERSA/.pico-sdk")  

# Incluir o SDK do Raspberry Pi Pico
include_directories(${PICO_SDK_PATH}/include)

# Defina a versão mínima do SDK do Raspberry Pi Pico
set(PICO_SDK_VERSION 1.5.0)

# Adicione o SDK do Raspberry Pi Pico
include_directories(${PICO_SDK_PATH}/include)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adicionar as bibliotecas externas (diretórios locais)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/FastLED-master)   # Biblioteca FastLED
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/Adafruit_SSD1306-master)  # Biblioteca Adafruit SSD1306
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/Adafruit-GFX-Library-master)  # Biblioteca Adafruit GFX

# Lista de bibliotecas adicionais que serão usadas no projeto
set(LIBRARIES
    FastLED
    Adafruit_SSD1306
    Adafruit_GFX
)

# Adicionar o executável para o projeto
add_executable(${PROJECT_NAME} main.cpp)

# Definir as dependências para o link
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    ${LIBRARIES}
)

# Adicionar as pastas que contêm cabeçalhos necessários
include_directories(
    ${PICO_SDK_PATH}/include
    ${PICO_SDK_PATH}/lib
    ${CMAKE_SOURCE_DIR}/lib/Adafruit_SSD1306-master  # Caminho da biblioteca Adafruit SSD1306
    ${CMAKE_SOURCE_DIR}/lib/FastLED-master  # Caminho da biblioteca FastLED
    ${CMAKE_SOURCE_DIR}/lib/Adafruit-GFX-Library-master  # Caminho da biblioteca Adafruit GFX
)

# Definir a saída do diretório de compilação
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adicionar a criação de binários extras para o microcontrolador
pico_add_extra_outputs(${PROJECT_NAME})
