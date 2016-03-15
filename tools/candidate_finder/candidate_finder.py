import sys
from os import listdir
from os.path import join, splitext


def candidate_finder(base_dir, min_val, max_val):
    asm_files = [f for f in listdir(base_dir) if splitext(f)[-1].lower().endswith("asm")]
    results = []
    for asm_file in asm_files:
        num_lines = sum(1 for _ in open(join(base_dir, asm_file)))
        if min_val <= num_lines <= max_val:
            results.append([asm_file, num_lines])
    final_results = sorted(results, key=lambda pulled_result: pulled_result[1])
    for result in final_results:
        print("Name: {0}, Number of Lines: {1}".format(result[0], result[1]))


if __name__ == "__main__":
    candidate_finder(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
