from typing import List

scrambeled = "b5xo1ar_gmcrirttdne8ohsoshf6t/:ewm1ea8a_2h4r/ms7cetH6nig2oss}__eyer6aot{_ea_/peot./4-2tho.fb7Bac7_rerr__/su1_n!5p8e/c.7Tlcm_saos_sdm_rpa6p3tl2recty_22ffemef_i0e03u-vl5enh9deru"

class Node:
    def __init__(self, next: int, value: int, secret: int):
        self.next = next
        self.value = value
        self.secret = secret

def extract_nodes_from_core_file() -> List[Node]:
    with open('core', 'rb') as f:
        core = f.read()

        i = core.find(b'\xC0\x32\xEA\x4B\x4E\x56\x00\x00')
        i2 = core.find(b'\xE0\x32\xEA\x4B\x4E\x56\x00\x00')
        baseAddr = int.from_bytes(core[i:i+8], byteorder='little') - i2

        nodes: List[Node] = []  # Add type hint for the nodes list
        while i:
            encoded_node = core[i:i+16]
            nextPtr = int.from_bytes(encoded_node[0:8], byteorder='little')
            addr = nextPtr - baseAddr if nextPtr - baseAddr > 0 else 0
            nodes.append(Node(addr, encoded_node[8], ord(scrambeled[encoded_node[8]])))
            i = addr

        return nodes

def unscramble(nodes: List[Node]) -> str:
    return ''.join(chr(node.secret) for node in nodes)

nodes = extract_nodes_from_core_file()
print(f"Unscrambled: {unscramble(nodes)}")