var p = 11, //два простых числа
    q = 17,
    modul = p * q, //модуль
    funEler = ((p - 1) * (q - 1)), //ф-я Эйлера
    openKey = funOpenKey(funEler), //получаем открытый ключ
    closeKey = funReverseNumber(openKey, funEler); //полчаем закрытый ключ

function testPrime(num1) { //ф-я проверки числа на простоту
    var testPr = true; //флаг 
    for (var i = 2; i < num1; i++) { //цикл по нашему числу
        if ((num1 % i) == 0) { //проверка деления на все его множители
            testPr = false; //если один из них, делится без остатка
            break; //то проверку не прошел и выходим из цикла
        }
    }
    return testPr; //возврат проверки простое/составное
}

function algoEuclid(num1, num2) { //ф-я проверки взаимопростоты
    var testEu = false, //флаг проверки 
        a = Math.max(num1, num2), //выбирается большее число
        b = Math.min(num1, num2), //выбирается меньшее число
        c = 0; //пер-я для хранения остака
    do { //цикл под нахождения остатка
        c = a % b; //находим остаток от деления
        a = b; //сдвигаем последовательность далее
        b = c;
        if (c == 1) //если остаток был равер 1
            testEu = true; //то числа взаимопростые
    }
    while (c != 0) //выполняется пока остаток не достигнет нуля
    return testEu; //возврат проверки взаимпопростые или нет
}

function funReverseNumber(num, mod) { //ф-я поиска обратного элемента по модулю
    if ((num == 0) || (algoEuclid(num, mod) == false)) //если элемент равен нулю или
        return 'Обратного элемента не существует'; //элемент и модуль не взаимопростые, то обраного элемента не существует
    var reverseNum = 1; //начало поиска с единицы
    while (((reverseNum * num) % mod) != 1) //проверяем равенство уравнения
        reverseNum++; //переходим к следующему числу
    return reverseNum; //возвращаем обратный элемент
}

function myPow(num, exp, mod) { //ф-я возведения num в степень exp и вычисления по модулю mod по итерациям
    var c = 1; //пер-я для хранения остатков
    for (var i = 0; i < exp; i++) { //цикл по степени
        c = (c * num) % mod; //умножаем на число и вычисляем модуль
    } //сохраняем остаток и умножаем его на число в след итерации 
    return c; //полученный остаток
}

function funOpenKey(funEler) { //ф-я получения открытого ключа

    var openKeyInFun = prompt('Введите открытый ключ Ко:'); //вводим открытый ключ
    //принцип проверки. есть три критерия, и если хоть один из них нарушен, то нужно проходить
    //все проверки заново, в приоритетном порядке. Например, если ввдоится не простое число, то
    //попросят ввести его еще раз, но проверка начнется с допустимых границ, а потом на простоту
    do {
        var testOpenKey = true; //флаг теста
        if (((openKeyInFun > 1) && (openKeyInFun <= funEler)) == 0) { //проверка границ введеного ключа
            openKeyInFun = prompt('Введеное число не в рамках. Введите число заново:'); //в противном случа, вводим заново
            testOpenKey = false; //флаг теста указывает что нужно проти проверку еще раз
        }
        if (testOpenKey == true) { //проверка флага теста
            if (testPrime(openKeyInFun) == false) { //проверка на простоту
                openKeyInFun = prompt('Введеное число не простое. Введите число заново:');
                testOpenKey = false; //флаг теста указывает что нужно проти проверку еще раз
            }
        }
        if (testOpenKey == true) { //проверка флага теста
            if (algoEuclid(openKeyInFun, funEler) == false) { //проверка на взаимопростоту
                openKeyInFun = prompt('Введеное число не взаимопростое. Введите число заново:');
                testOpenKey = false; //флаг теста указывает что нужно проти проверку еще раз
            }
        }
    } while (testOpenKey == false) //пока все тесты не будут продейны без проблем
    return openKeyInFun; //введеный открытый ключ
}

function funCipherText(getText, openKey, modul) { //ф-я шифрования текста
    var cipherTextInFun = ''; //переменная для хранения зашифрованного текста
    for (var i = 0; i < getText.length; i++) { //проходим по всем символам полученного текста
        cipherTextInFun += String.fromCharCode(myPow(getText.charCodeAt(i), openKey, modul));
    } //берется код символа,  возводится в степень открытого ключа, вычисляется по модулю
    //потом преобразовывается по полученому юни-коду к символу и склеивается в зашифр-ю строчку
    return cipherTextInFun; //зашифрованый текст
}

function funDecipherText(cipherText, closeKey, modul) { //ф-я дешифровки текста
    var deCipherTextInFun = ''; //переменная для хранения дешифрованного текста
    for (var i = 0; i < cipherText.length; i++) { //проходим по всем символам зашифрованного текста
        deCipherTextInFun += String.fromCharCode(myPow(cipherText.charCodeAt(i), closeKey, modul));
    } //берется код символа,  возводится в степень закрытого ключа, вычисляется по модулю
    //потом преобразовывается по полученому юни-коду к символу и склеивается в дешифр-ю строчку
    return deCipherTextInFun;
}

var getText = prompt('Введите текст для шифрования:'); //вводим текст для шифрования

var cipherText = funCipherText(getText, openKey, modul); //вызов ф-ии шифрования
alert(cipherText); //вывод зашифрованного текста

var deсipherText = funDecipherText(cipherText, closeKey, modul); //вызов ф-ии дешифрования
alert(deсipherText); //вывод дешифрованного текста
