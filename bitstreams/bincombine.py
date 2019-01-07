import sys
import io

# Combines binary files based on provided offsets
# Example of usage:
# python bincombine.py -o res.bin 0x0 HumanPresence_Bitstream.bin 0x20000 HumanPresence_Firmware.bin
# python bincombine.py -output res.bin 0x0 HumanPresence_Bitstream.bin 0x20000 HumanPresence_Firmware.bin
# Or skip result file, it's default name is defined in script's variable:
# python bincombine.py 0x0 HumanPresence_Bitstream.bin 0x20000 HumanPresence_Firmware.bin


print('Args: {}'.format(sys.argv))

offset2file = {}

args = sys.argv[1:]

toHex = lambda x: "0x{:02X}".format(x)

# Result file
resultfilename = "combined.bin"

for offset,file in zip(args[0::2], args[1::2]):
    if offset in ['-o', '--output']:
        resultfilename = file
    else:
        print '{}: {}'.format(offset, file)
        offset2file[int(offset, 0)] = file

resultFile = open(resultfilename, 'wb')
offsets = list(offset2file.keys())
offsets.sort()

current_pos = 0
for idx in range(0, len(offsets)):
    offset = offsets[idx]
    print('{} {}'.format(idx, offset))
    if current_pos > offset:
        raise ValueError('Memory locations overlap: {} overlaps with provided offset {}'.format(toHex(current_pos), toHex(offset)))
    positions_diff = offset - current_pos

    for byte in range(0, positions_diff):
        # print('Addind placeholder byte {} at position {}'.format(toHex(255),toHex(current_pos)))
        print('Addind placeholder byte {} at position {}'.format(toHex(255),toHex(current_pos)))
        resultFile.write(b'\xff')
        current_pos += 1

    filename = offset2file[offset]
    file_content = io.open(filename, 'rb').read()

    resultFile.write(file_content)
    current_pos += len(file_content)
