import matplotlib.pyplot as plt
import sys

def generate_graph(file: str, line_color: str):
    edges = parse_data(file)

    plt.rcParams["figure.figsize"] = [7.50, 3.50]
    plt.rcParams["figure.autolayout"] = True
    plt.gca().set_aspect('equal',adjustable='box')

    for e in edges:
        x_values = [e[0], e[2]]
        y_values = [e[1], e[3]]

        plt.plot(x_values, y_values, color=line_color)

    plt.show()

    
    
def parse_data(file:str):

    lines_file = open(file)
    unformatted_edges = lines_file.read()
    lines_file.close()
    unformatted_edges = unformatted_edges.split('\n')
    edges = []

    for edge in unformatted_edges:
        if len(edge) > 0:
            points_to_parse = edge.split(";")
            edge = []
            for p in points_to_parse:
                x, _, y = p.strip().partition(',')
                x = float(x.partition('(')[2].strip())
                edge.append(x)

                y = float(y.partition(')')[0].strip())
                edge.append(y)

            edges.append(edge)
    
    return edges




if __name__ == "__main__":

    if len(sys.argv) != 3:
        raise RuntimeError('need two program arguments')


    generate_graph(sys.argv[1], sys.argv[2])

