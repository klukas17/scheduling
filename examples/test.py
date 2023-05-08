import os

RED = "\x1B[31m"
GREEN = "\x1B[32m"
END = "\x1B[0m"

valid_examples = 0
total_examples = 0

subdirs = os.listdir(".")
subdirs.sort()

for subdir in subdirs:
    if os.path.isdir(subdir) and subdir.startswith("example_"):
        expected_logs_dir = os.path.join(subdir, "expected_logs_per_job")
        simulator_logs_file = os.path.join(subdir, "simulator_logs.txt")

        is_valid = True
        job_logs = []

        expected_logs = os.listdir(expected_logs_dir)
        expected_logs.sort()

        for expected_log_file in expected_logs:

            job_id = int(expected_log_file.split(".")[0].split("_")[1])
            expected_log_path = os.path.join(expected_logs_dir, expected_log_file)

            with open(expected_log_path, "r") as f:
                expected_contents = f.read()

            with open(simulator_logs_file, "r") as f:
                job_contents = "".join([line for line in f if f"Job {job_id}:" in line])

            if expected_contents == job_contents:
                job_logs.append(f"  {GREEN}[✔]{END} Job {job_id}")
            else:
                job_logs.append(f"  {RED}[✘]{END} Job {job_id}")
                is_valid = False

        if is_valid:
            print(f"{GREEN}[✔]{END} Example {subdir}")
            valid_examples += 1
        else:
            print(f"{RED}[✘]{END} Example {subdir}")

        total_examples += 1

        for job_log in job_logs:
            print(job_log)

print(f"\nScore: {valid_examples}/{total_examples}")
