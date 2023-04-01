#!/bin/bash

LEADERBOARD_URL="http://mcs.ugr.es/p1"

# Check last update
last_update=$(git ls-remote https://github.com/ugr-ccia-IA/practica1.git HEAD | awk '{print $1}')
if git merge-base --is-ancestor $last_update main; then
    echo "Repositorio actualizado"
else
    echo "Actualiza el repositorio con los cambios del profesor antes de ejecutar el leaderboard"
    exit 1
fi
# Save commits list
COMMITS_LIST=$(git log --format="%H")

# if 1st argument is "clean", remove .leaderboard_config
if [ "$1" = "clean" ]; then
    rm .leaderboard_config
fi

# if 1st argument is "stealth", set mode to stealth
if [ "$1" = "stealth" ]; then
    LEADERBOARD_MODE="stealth"
else
    LEADERBOARD_MODE="normal"
fi

echo "Instalando dependencias..."
python3 -c 'import sys; assert sys.version_info[:][1] >= 8' || (echo "Instalando python3.8..." && sudo apt install software-properties-common && sudo add-apt-repository ppa:deadsnakes/ppa && sudo apt install python3.8 && sudo ln -s /usr/bin/python3.8 /usr/bin/python3) || exit 1

echo "Eliminando archivos de compilación..."
rm -r build CMakeCache.txt CMakeFiles cmake_install.cmake Makefile practica1 practica1SG 2> /dev/null

echo "Compilando proyecto..."
mkdir build
cd build
cmake ..
make -j 4 practica1SG
cd ..

# if .leaderboard_config doesn't exists, ask for user and group
if [ ! -f .leaderboard_config ]; then
    echo "Nombre de usuario (Solo letras sin acentos, números y espacios)"
    echo "Ejemplo: Guillermo Gomez"
    echo -n "> "
    read LEADERBOARD_NAME
    echo "Nombre del grupo (Una letra mayúscula seguida de un número)"
    echo "Los alumnos de los dobles grados utilziarán el sufijo D"
    echo "Ejemplo: A1 o A1D"
    echo -n "> "
    read LEADERBOARD_GROUP
    # save user and group to .leaderboard_config
    echo "LEADERBOARD_NAME=\"$LEADERBOARD_NAME\"" > .leaderboard_config
    echo "LEADERBOARD_GROUP=\"$LEADERBOARD_GROUP\"" >> .leaderboard_config

# else read user and group from .leaderboard_config
else
    source .leaderboard_config
fi

echo "Running tests..."
# LEADERBOARD_NAME=$LEADERBOARD_NAME LEADERBOARD_GROUP=$LEADERBOARD_GROUP LEADERBOARD_URL=$LEADERBOARD_URL python3 leaderboard.py

LEADERBOARD_NAME=$LEADERBOARD_NAME LEADERBOARD_GROUP=$LEADERBOARD_GROUP LEADERBOARD_URL=$LEADERBOARD_URL COMMITS_LIST=$COMMITS_LIST LEADERBOARD_MODE=$LEADERBOARD_MODE python3 - <<END
import subprocess
import os
import time
import sys
import json
from collections import namedtuple
from itertools import chain

# Assert LEADERBOARD_NAME, LEADERBOARD_GROUP and LEADERBOARD_URL is set and COMMITS_LIST is set
assert "LEADERBOARD_NAME" in os.environ, "LEADERBOARD_NAME not set"
assert "LEADERBOARD_GROUP" in os.environ, "LEADERBOARD_GROUP not set"
assert "LEADERBOARD_URL" in os.environ, "LEADERBOARD_URL not set"
assert "COMMITS_LIST" in os.environ, "COMMITS_LIST not set"
assert "LEADERBOARD_MODE" in os.environ, "LEADERBOARD_MODE not set"

user_name = os.environ["LEADERBOARD_NAME"]
user_group = os.environ["LEADERBOARD_GROUP"]
leaderboard_url = os.environ["LEADERBOARD_URL"]
commits_list = os.environ["COMMITS_LIST"].split("\n")
leaderboard_mode = os.environ["LEADERBOARD_MODE"]


# Copied from https://stackoverflow.com/questions/3173320/text-progress-bar-in-terminal-with-block-characters/13685020
def progressBar(iterable, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iterable    - Required  : iterable object (Iterable)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    total = len(iterable)
    # Progress Bar Printing Function
    def printProgressBar (iteration):
        percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
        filledLength = int(length * iteration // total)
        bar = fill * filledLength + '-' * (length - filledLength)
        print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
    # Initial Call
    printProgressBar(0)
    # Update Progress Bar
    for i, item in enumerate(iterable):
        yield item
        printProgressBar(i + 1)
    # Print New Line on Complete
    print()

GENERATE_RESULTS = False

Test = namedtuple(
    "Test",
    [
        "name",
        "group",
        "public",
        "description",
        "binary",
        "args",
        "level",
        "ifile",
        "testfunc",
        "testargs",
        "call",
    ],
    defaults=[None] * 10,
)
Result = namedtuple(
    "Result",
    [
        "name",
        "group",
        "success",
        "call",
        "level",
        "public",
        "description",
        "stdout",
        "stderr",
        "err",
        "result"
    ],
    defaults=[None] * 10,
)


def run_process(bin_full_path, args, input_file=None):
    retcode = stdout = stderr = err = None
    try:
        f = open(input_file, "r") if input_file else None
        result = subprocess.run(
            [bin_full_path] + args.split(),
            stdin=f,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if f is not None:
            f.close()
        stdout = result.stdout.decode("utf-8")
        stderr = result.stderr.decode("utf-8")
        retcode = result.returncode
    except Exception as e:
        err = e

    return (retcode, err, stdout, stderr)

    """Instantes de simulacion no consumidos: 2833
Tiempo Consumido: 0.000663
Nivel Final de Bateria: 0
Colisiones: 0
Reinicios: 0
Porcentaje de mapa descubierto: 69.2222
    """
def parse_stdout(stdout):
    msg = err = None
    success = True
    try:
        msg = [float(l.split(": ")[-1]) for l in stdout.split("\n")[-7:-1]]
        assert len(msg) == 6
        msg = dict(zip(["no_consumido","tiempo", "bateria", "colisiones", "reinicios", "mapa"], msg))
    except Exception as e:
        success = False
        print("error")
        err = e

    return err, success, msg

BINARY_PATH = "./build/"
FUNC_LIB = {"parse_stdout": parse_stdout}

good_tests = lambda r,c,o,l: not (l > 0 and o != 0)

mapa_30 = [
    Test(
        name="mapa_30",
        group="mapa_30",
        public=True,
        binary="practica1SG",
        args=f"mapas/mapa30.map 0 {l} {r} {c} {o}",
        level=l,
        testfunc="parse_stdout",
    )
    for r,c in [
        (3,3), # Esquina superior izquierda
        (25,11), # Como ejemplo
        (22,11), # Dentro del castillo
        (8,14), # Dentro del agua
        (7,26) # Borde
        ]
    for o in [0,1,3]
    for l in [0,1,2,3]
    if good_tests(r,c,o,l)
]

mapa_50 = [
    Test(
        name="mapa_50",
        group="mapa_50",
        public=True,
        binary="practica1SG",
        args=f"mapas/mapa50.map 0 {l} {r} {c} {o}",
        level=l,
        testfunc="parse_stdout",
    )
    for r,c in [
        (42,19), # Como ejemplo
        (7,9), # Rodeado de bosque
        (9,42), # Rodeado de agua
        ]
    for o in [0,2,4,5]
    for l in [0,1,2,3]
    if good_tests(r,c,o,l)
]

mapa_75 = [
    Test(
        name="mapa_75",
        group="mapa_75",
        public=True,
        binary="practica1SG",
        args=f"mapas/mapa75.map 0 {l} {r} {c} {o}",
        level=l,
        testfunc="parse_stdout",
    )
    for r,c in [
        (63,29), # Hemisferio sur
        (23,29), # Hemisferio norte
        (34,60), # Dentro del castillo
        (34,21) # Encima de 'G'
        ]
    for o in [0,1,3]
    for l in [0,1,2,3]
    if good_tests(r,c,o,l)
]

test_list = list(chain(
    mapa_30,
    mapa_50,
    mapa_75
))

from collections import Counter

# assert_unique = Counter([e.name for e in test_list]).most_common(1)[0][1] == 1
# assert assert_unique

test_results = []

for t in progressBar(test_list, length = 40):
    name = t.name
    public = t.public
    group = t.group
    description = t.description
    call = f"{t.binary} {t.args}"
    level = t.level
    test_err = None

    success = True
    if t.binary:
        bin_full_path = os.path.join(BINARY_PATH, t.binary)
        retcode, err, stdout, stderr = run_process(bin_full_path, t.args, t.ifile)
        success = not (err or (retcode != 0))
        if err:
            test_err = err

    if (not GENERATE_RESULTS) and success and t.testfunc:
        err, success, message = FUNC_LIB[t.testfunc](stdout)

        if not success:
            stdout = message
        if err:
            test_err = err

    result = Result(
        name=name,
        group=group,
        success=success,
        public=public,
        call=call,
        level=level,
        description=description,
        # stdout=stdout,
        # stderr=stderr,
        err=str(test_err) if test_err else None,
        result=message if success else None
    )

    test_results.append(result._asdict())

# if GENERATE_RESULTS:
#     print([e["success"] for e in test_results])
#     with open(OUTPUT_JSON_PATH, "w") as ofile:
#         d = {e["name"]: e["stdout"] for e in test_results}
#         s = json.dumps(d)
#         ofile.write(s)
#         print(json.dumps(d, indent=2))
# else:
# print(json.dumps(test_results, indent=2))
import requests

r = requests.post(leaderboard_url, json={
        'user': user_name,
        'group': user_group,
        'execution_results': test_results,
        'commits_list': commits_list,
        'version': '2',
        'stealth': leaderboard_mode == 'stealth'
    })
print(r.status_code)
print(r.text)
END
