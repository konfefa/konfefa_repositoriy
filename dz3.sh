#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Использование: $0 <имя_файла>"
    exit 1
fi

filename=$1

add_expense() {
    echo -n "Введите дату: "; read date
    echo -n "Введите категорию: "; read category
    echo -n "Введите сумму: "; read amount
    echo -n "Введите описание: "; read description
    
    echo "$date|$category|$amount|$description" >> "$filename"
    echo "Запись добавлена!"
}

view_expenses() {
    if [ ! -f "$filename" ]; then
        echo "Файл не существует"
        return
    fi
    
    echo "=== ЗАПИСИ О РАСХОДАХ ==="
    cat "$filename"
    echo "=========================="
}

while true; do
    echo "1 - Добавить запись"
    echo "2 - Просмотреть записи"
    echo "3 - Выйти"
    echo -n "Выберите действие: "
    read choice
    
    case $choice in
        1) add_expense ;;
        2) view_expenses ;;
        3) exit 0 ;;
        *) echo "Неверный выбор" ;;
    esac
    echo
done
