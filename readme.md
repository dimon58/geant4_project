## Запуск

Для запуска нужно установить:

- [geant4](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/)
- [root](https://root.cern/)

### Для запуска в IDE

Так же в переменное окружение нужно добавить переменную `Geant4_DIR=/path-to-geant4-installation/lib/cmake/Geant4/`.
Если собираете через консоль, то можно загрузить все требуемые переменные окружения командой `source geant4.sh`.

### Альтернатива

- Скомпилируйте проект `. build.sh`
- Запустите `./build/geant4_project`

## Моделирование

Результаты моделирования будут сохранены в папку `resuts` в файл `result.root`