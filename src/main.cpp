
#include "../include/bitmap.hpp"
#include "../include/colors.hpp"

#include <unistd.h>
#include <getopt.h>

void help() {
    printf("[-h] or [--help]:\n\tcalling help.\n");
    printf("[-l] or [--load] <filename>:\n\tloading image from file.\n");
    printf("[-s] or [--save] <filename>:\n\tsaving image to file.\n");
    printf("[-w] or [--pen_width] <width>:\n\tset pen width.\n");
    printf("[-p] or [--pen_color] <color>:\n\tset pen color.\n");
    printf("[-b] or [--brush_color] <color>:\n\tset brush color.\n");
    printf("[-r] or [--rectangle] <x1> <y1> <x2> <y2>:\n\tdrawing empty rectangle.\n");
    printf("[-R] or [--fill_rect] <x1> <y1> <x2> <y2>:\n\tdrawing filled rectangle.\n");
    printf("[-f] or [--flip] <x1> <y1> <x2> <y2> <angle>:\n\trotating a piece of image to an angle.\n");
    printf("[-c] or [--fractal] <x1> <y1> <x2> <y2> <fractalType (1-3)>\n\tdrawing fractal\n");
    printf("[-i] or [-information]:\n\tprinting information about image.\n");
}

static struct option long_options[] = {
    {"help",        no_argument,        0,  'h'},
    {"load",        required_argument,  0,  'l'},
    {"save",        required_argument,  0,  's'},
    {"pen_width",   required_argument,  0,  'w'},
    {"pen_color",   required_argument,  0,  'p'},
    {"brush_color", required_argument,  0,  'b'},
    {"rectangle",   required_argument,  0,  'r'},
    {"fill_rect",   required_argument,  0,  'R'},
    {"flip",        required_argument,  0,  'f'},
    {"fractal",     required_argument,  0,  'c'},
    {"information", no_argument,        0,  'i'},
    {0, 0, 0, 0}
};

int main(int argc, char * argv[]) {
    ColorTable colorTable;
    Bitmap image;
    LONG x1;
    LONG y1;
    LONG x2;
    LONG y2;
    int an;
    int ft;

    int index_test = 0;
    int c;
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "hl:s:w:p:b:R:z:f:c:i?", long_options, &option_index)) != -1) {
        index_test++;
        switch (c) {
        case 'h':
            // Вывести помощь.
            break;
        case 'l':
            image.load(optarg);
            break;
        case 's':
            image.save(optarg);
            break;
        case 'w':
            image.set_pen_width(atoi(optarg));
            break;
        case 'p':
            image.set_pen_color(colorTable.get_color(optarg));
            break;
        case 'b':
            image.set_brush_color(colorTable.get_color(optarg));
            break;
        case 'r':
            if (argc - optind + 1 < 4) {
                printf("There are not enough arguments. (Expected 4)\n");
                return -1;
            }
            x1 = atoi(argv[optind++ - 1]);
            y1 = atoi(argv[optind++ - 1]);
            x2 = atoi(argv[optind++ - 1]);
            y2 = atoi(argv[optind - 1]);
            image.draw_rectangle(x1, y1, x2, y2);
            break;
        case 'R':
            if (argc - optind + 1 < 4) {
                printf("There are not enough arguments. (Expected 4)\n");
                return -1;
            }
            x1 = atoi(argv[optind++ - 1]);
            y1 = atoi(argv[optind++ - 1]);
            x2 = atoi(argv[optind++ - 1]);
            y2 = atoi(argv[optind - 1]);
            image.draw_rectangle(x1, y1, x2, y2, true);
            break;
        case 'f':
            if (argc - optind + 1 < 5) {
                printf("There are not enough arguments. (Expected 5)\n");
                return -1;
            }
            x1 = atoi(argv[optind++ - 1]);
            y1 = atoi(argv[optind++ - 1]);
            x2 = atoi(argv[optind++ - 1]);
            y2 = atoi(argv[optind++ - 1]);
            an = atoi(argv[optind - 1]) / 90 % 4;
            image.flip(x1, y1, x2, y2, an);
            break;
        case 'c':
            if (argc - optind + 1 < 5) {
                printf("There are not enough arguments. (Expected 5)\n");
                return -1;
            }
            x1 = atoi(argv[optind++ - 1]);
            y1 = atoi(argv[optind++ - 1]);
            x2 = atoi(argv[optind++ - 1]);
            y2 = atoi(argv[optind++ - 1]);
            ft = atoi(argv[optind - 1]);
            switch (ft) {
            case 1:
                image.fractal_1(x1, y1, x2, y2);
                break;
            case 2:
                image.fractal_2(x1, y1, x2, y2);
                break;
            case 3:
                image.fractal_3(x1, y1, x2, y2);
                break; 
            default:
                printf("Unknown fractal...\n");
                return -1;
            }
            break;
        case 'i':
            image.print_info();
            break;
        case '?':
            printf("Shit happens)\n");
            break;
        default:
            abort();
        }
    } 
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    
    }
    return 0;
}


/*
    case 0:
        // If this option set a flag, do nothing else now. 
        if (long_options[option_index].flag != 0)
            break;
        printf ("option %s", long_options[option_index].name);
        if (optarg)
            printf (" with arg %s", optarg);
        printf ("\n");
        break;
*/

/*
    
    -p  --pixel
        LONG x;
        LONG y;
    --line
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
    -r  --rectangle
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
    --filled_rectangle
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
    --circle
        LONG x;
        LONG y;
        LONG r;
    --filled_circle
        LONG x;
        LONG y;
        LONG r;
    -f  --flip
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
        LONG count;
*/