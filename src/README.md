# Basic CI/CD

Разработка простого **CI/CD** для проекта *SimpleBashUtils*. Сборка, тестирование, развертывание.


## Contents

1. [Настройка gitlab-runner](#part-1-настройка-gitlab-runner)  
2. [Сборка](#part-2-сборка)  
3. [Тест кодстайла](#part-3-тест-кодстайла)   
4. [Интеграционные тесты](#part-4-интеграционные-тесты)  
5. [Этап деплоя](#part-5-этап-деплоя)  
6. [Дополнительно. Уведомления](#part-6-дополнительно-уведомления)

## Part 1. Настройка **gitlab-runner**

1. Добавим официальный репозиторий.

```bash
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
```

2. Установим последнюю версию GitLab Runner.

```bash
sudo apt-get install gitlab-runner
```

3. Сделаем автозапуск сервиса и запустим его.

```bash
# разрешаем автозапуск сервиса и стартуем его
systemctl enable gitlab-runner --now
```

4. Зарегистрируем runner. При регистрации теги не создавала, чтобы запускать задачи без тегов. Иначе все задачи должны будут запускаться с тегами. В качестве исполнителя выбран shell, так как в CI буду запускать shell-команды.

```bash
sudo gitlab-runner register
```

![1](../misc/images/1.png)


## Part 2. Сборка

- В .gitlab-ci.yml пропишем стейджи и цели для сборки:

```yml
stages:
  - build
  - test_style
  - integration_test
  - deploy

build-cat:
  stage: build
  script:
    - cd src/project/cat/ && make build
  artifacts:
    paths: 
      - src/project/cat/s21_cat
    expire_in: 30 days

build-grep:
  stage: build
  script:
    - cd src/project/grep/ && make build
  artifacts:
    paths:
      - src/project/grep/s21_grep
    expire_in: 30 days
```
## Part 3. Тест кодстайла

- Для проверки на стиль кода важно, чтобы на сервере соответствующая утилита была установлена.

```bash
sudo apt-get install clang-format
```

- В .gitlab-ci.yml пропишем цели для теста на код-стайл. Также важно указать зависимость от предыдущего этапаи запуск в случае, если предыдущая стадия была выполнена успешно.

```yml
style-cat:
  stage: test_style
  needs: ["build-cat"]
  script: 
    - cd src/project/cat/ && clang-format -n -Werror *.c
  when: on_success

style-grep:
  stage: test_style
  needs: ["build-grep"]
  script: 
    - cd src/project/grep/ && clang-format -n -Werror *.c
  when: on_success
```


## Part 4. Интеграционные тесты

- В .gitlab-ci.yml пропишем цели для запуска тестов. Также важно указать зависимость от предыдущего этапаи запуск в случае, если предыдущая стадия была выполнена успешно.

```yml
test-cat:
  stage: integration_test
  needs: ["build-cat", "style-cat"]
  script: 
    - cd src/project/cat/ && make test
  when: on_success

test-grep:
  stage: integration_test
  needs: ["build-grep", "style-grep"]
  script: 
    - cd src/project/grep/ && make test
  when: on_success
```

- Сам тестовый скрипт возвращает 0 в случае успешного выполения всех тестов и 1 в случае ошибки.

## Part 5. Этап деплоя

## Part 6. Дополнительно. Уведомления