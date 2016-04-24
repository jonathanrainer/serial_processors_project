import sys
from os import listdir
from os.path import join, splitext


def candidate_finder(base_dir, min_val, max_val):
    """
    Produce a list of files that have line length between min_val and max_val.
    Providing a quick way to cull a lot of very simple examples quickly to focus
    on differentiating the more complex cases.
    :param base_dir: A directory to search, can be provided either absolute or
    relative though absolute is preferred.
    :param min_val: An integer to represent the minimum number of lines to
    be considered
    :param max_val: An integer to represent the maximum number of lines to be
     considered.
    :return: Nothing.
    """
    # Grab a list of all the files in a directory only if the file extension is
    # asm.
    asm_files = [f for f in listdir(base_dir)
                 if splitext(f)[-1].lower().endswith("asm")]
    # Create a list to hold all the results
    results = []
    # Iterate over the asm files
    for asm_file in asm_files:
        # Count how many lines are in each file
        num_lines = sum(1 for _ in open(join(base_dir, asm_file)))
        # If the number of lines is within the given interval then append the
        # file and how many lines it has to the results list
        if min_val <= num_lines <= max_val:
            results.append([asm_file, num_lines])
    # Sort the files that have been found by the number of lines they have
    final_results = sorted(results, key=lambda pulled_result: pulled_result[1])
    # Print out each one in turn.
    for result in final_results:
        print("Name: {0}, Number of Lines: {1}".format(result[0], result[1]))
    return


if __name__ == "__main__":
    # Call the candidate finder with all the arguments as given on the command
    # line.
    candidate_finder(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
