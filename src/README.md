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

## Part 3. Тест кодстайла

## Part 4. Интеграционные тесты

## Part 5. Этап деплоя

## Part 6. Дополнительно. Уведомления