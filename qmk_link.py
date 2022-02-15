#!/usr/bin/env python

import os
import subprocess

user_name = "CarlAndersson"
boards = {"kyria": "splitkb/kyria"}
keymap_home = os.path.dirname(os.path.realpath(__file__))
qmk_home = os.path.join(keymap_home, "qmk_firmware")


def make_link(source, target):
    if not os.path.exists(target):
        print('Linking:', source, '\n\t|->', target)
        subprocess.run(['ln', '-s', source, target])


def delete_link(target):
    if os.path.exists(target):
        print('Uninking:', target)
        subprocess.run(['rm', '-rf', target])


def link_board(board, unlink=False):
    target = os.path.join(qmk_home, "keyboards", boards[board], "keymaps", user_name)
    source = os.path.join(keymap_home, board)
    if unlink:
        delete_link(target)
    else:
        make_link(source, target)


def link_user(unlink=False):
    target = os.path.join(qmk_home, "users", user_name)
    source = os.path.join(keymap_home, user_name)
    if unlink:
        delete_link(target)
    else:
        make_link(source, target)


def setup_links(unlink=False):
    link_user(unlink=unlink)
    for board in boards:
        link_board(board, unlink=unlink)


def write_config(config, value):
    output = subprocess.run(['qmk', 'config', config], capture_output=True)
    current = output.stdout.decode()[len(config) + 1:].strip()
    if current != value:
        subprocess.run(['qmk', 'config', f'{config}={value}'])


def config_homes():
    write_config('user.qmk_home', qmk_home)
    write_config('user.keymap', user_name)


def config_board(board):
    write_config('user.keyboard', boards[board])


if __name__ == "__main__":
    import argparse
    import textwrap
    parser = argparse.ArgumentParser(
        description='Manage linked qmk installation',
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument(
        'task',
        help=textwrap.dedent('''\
            What task to perform.
            symlinks: configures the symlinks for the user space and all keyboards
            delink: clear the symlinks
            config: add the correct qmk home folder to the global qmk config
            other: set the default keyboard
        '''),
        choices=['symlinks', 'delink', 'config'] + list(boards),
    )

    args = parser.parse_args()

    if args.task == 'symlinks':
        setup_links()
    elif args.task == 'delink':
        setup_links(unlink=True)
    elif args.task == 'config':
        config_homes()
    elif args.task in boards:
        config_board(args.task)
