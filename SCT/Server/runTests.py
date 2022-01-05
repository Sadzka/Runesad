import os
import subprocess

print(os.getcwd())
build_dir = os.getcwd() + "/../../cmake-build-debug"
path_server = build_dir + "/Server.exe"

sct_name_list = []
for (dirpath, dirnames, filenames) in os.walk("./bin/"):
    sct_name_list.extend(filenames)
    break

verdict_list = []
for sct_name in sct_name_list:
    server_process = subprocess.Popen(path_server, cwd=build_dir, stdout=subprocess.DEVNULL)
    sct_process = subprocess.Popen("bin/" + sct_name, cwd=build_dir)

    exit_code = sct_process.wait()

    if exit_code == 0:
        verdict_list.append((sct_name, "passed!"))
    else:
        verdict_list.append((sct_name, "failed!"))

    server_process.kill()
    sct_process.kill()

for test_name, result in verdict_list:
    print("{} {}".format(test_name, result))
