# VerKer
ACSL specifications for linux kernel functions

Проект по разработке спецификаций и формальному доказательству корректности библиотечных функций ядра Linux.

# Инструментарий

Спецификации разрабатываются на языке ACSL. В качестве инструментов формальной верификации используются Frama-C с плагином дедуктивной верификации jessie.
- Описание, как установить инструменты можно найти по [ссылке](https://forge.ispras.ru/projects/astraver/wiki).Инструменты работают на Linux, Windows, Mac OS X.
- По [ссылке](https://www.dropbox.com/s/45sjzvfakz2n316/verification.ova?dl=0) можно загрузить образ виртуальной машины VirtualBox в формате ova с уже с предустановленными и настроенными инструментами. Размер образа ~3.6 гигабайт. Ос - Ubuntu. Логин - user. Пароль - 1. В директории **workspace** находятся два репозитория. Один соответствует данному, второй - acsl-proved (примеры с протоколами верикации).

# Организация файлов в репозитории

Каждая библиотечная функция ядра Linux располагается в отдельном *.c файле. В соответствующем *.h файле находятся объявления, типы, структуры, специфичные для данной функции.
- В **kernel_definitons.h** файле находятся общие для всех функции типы, макросы и прочие декларации.
- В **ctype.h** находятся сразу несколько функций, которые изначально в ядре были макросами. Для удобства формальной верификации данные макросы (islower,isupper,isdigit,...) были переписаны как inline функции.

# Организация спецификаций

Контракт (предусловие и постусловие) находятся для каждой доказанной функции в соответствующем заголовочном файле (например, strlen.h). В нем же находятся леммы/аксиомы/логические функции, если они разработаны для соответствующей функции.

В *.c файле находится тело функции с инвариантами циклов, оценочными функциями и ассертами.

Для некоторых функций спецификации избыточны и фактически дважды по разному описывают то, как функций должна функционировать. Например, одна из таких функций - strlen. В её спецификации есть обычные функциональные требования и есть требование на соответствие возвращаемого результата вызову логической функции под тем же названием strlen. Чем мотивирована подобная "избыточность"? Логическую функцию strlen удобно использовать в спецификациях других функций, например, strcmp (а логическую функции, описывающую поведение функции strcmp при описании функциональных требований к strcpy). При этом все основные свойства логической функции выражаются через леммы (леммы на данном этапе не доказываются). Такие спецификации невозможно отобразить в проверки времени исполнения E-ACSL. Поэтому для тех функций, которым в спецификациях ставится в соответствие логическая функция, обязательно есть и "обычные" спецификации.

Как выбирается будет ли для функции разработана такая избыточная спецификация?
1) Обычной функции можно сопоставить логическую функцию (один-в-один), только если функция на языке Си "чистая" (pure).
2) Логическую функцию рационально писать в том случае, если они пригодится для разработки спецификаций в том числе и для других функций. Например, в функциональных требованиях к memcpy можно выразить "одинаковость" src и dest посредством вызова логической функции memcmp.

Протоколы доказательств (запусков солверов) на текущий момент в репозиторий не включены. Это будет сделано чуть позже, когда будет доказано большее количество функций. На текущий момент, когда спецификации ещё дорабатываются, это лишь "замусорит" репозиторий огромным количеством объемных файлов.

На данном этапе корректность лемм в спецификациях никак не доказывалась. Соответственно, в них могут быть ошибки. Леммы будут доказаны на втором этапе, когда все основные спецификации зафиксированы и будут выкладываться протоколы доказательств. Корректность лемм будет доказана посредством Coq или же лемма-функций, поддерка которых появится в одном из следующий релизов инструментария.

# Запуск инструментов

```
$ frama-c -jessie <func>.c
$ frama-c -jessie check_bytes8.c
```
Либо
```
$ make verify-<func>
$ make verify-check_bytes8
```

# Статус доказательства

| ID | Function | Status | Logic function | Comment |
|----|----------|--------|----------------|---------|
| 1 | check_bytes8 | proved | proved | |
| 2 | match_string | | not required | |
| 3 | memchr | proved | | |
| 4 | memcmp | proved | | |
| 5 | memscan | proved | not required | |
| 6 | skip_spaces | proved | proved | requires too strict (remove strlen) |
| 7 | strcasecmp | proved | | |
| 8 | strcat | | not required | |
| 9 | strchr | proved | proved | |
| 10 | strchrnul | proved | proved | |
| 11 | strcmp | proved | | |
| 12 | strcpy | proved | not required | use strcmp logic function |
| 13 | strcspn | proved | proved | |
| 14 | strim | | not required | |
| 15 | strlen | proved | proved | |
| 16 | strncasecmp | | | |
| 17 | strncat | | not required | |
| 18 | strnchr | proved | | |
| 19 | strncmp | | | |
| 20 | strncpy | | not required | |
| 21 | strnlen | proved | proved | |
| 22 | strnstr | | | |
| 23 | strpbrk | proved | proved | |
| 24 | strrchr | proved | | |
| 25 | strreplace | | | |
| 26 | strsep | proved | not required | |
| 27 | strspn | proved | proved | |
| 28 | strstr | | | |
| 29 | sysfs_streq | | | |
| 30 | strlcat | | not required | |
| 31 | strlcpy | proved | not required | use strncmp lf in in ensures |
| 32 | memmove | proved | not required | use memcmp logic function at ensures |
| 33 | memcpy | proved | not required | use memcmp logic function at ensures |
| 34 | memset | proved | not required | |
| 35 | kstrtobool | proved | not required | |
| 36 | parse\_int\_radix | proved | not required | |
