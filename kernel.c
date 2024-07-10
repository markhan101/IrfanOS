#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "serial.h"
#include "vga.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	terminal_initialize();

	terminal_writestring("Welcome to the kernel.\nThis is happening on a new line wowwww.");
	int init = init_serial();
	write_serial('s');
	write_serial('N');
	write_serial('\n');
	write_serial('u');
	// terminal_writestring("In the tranquil expanse of the Pacific Northwest, where the towering firs weave a canopy above the winding trails, lies a hidden sanctuary known as Whispering Pines. This remote retreat, nestled against the backdrop of mist-laden mountains, is a place where time seems to slow and the soul finds solace in the rhythm of nature's gentle cadence. As dawn breaks over the horizon, a symphony of birdsong greets the awakening day, blending harmoniously with the soft rustle of leaves in the morning breeze. The air carries the faint scent of pine and earth, infused with the freshness of dew-kissed grass. Sunlight filters through the canopy above, casting dappled patterns of light and shadow on the forest floor. Trails meander through the woods, leading explorers past ancient cedar trees whose gnarled roots embrace the moss-covered ground. Occasionally, a glimpse of wildlife—a deer cautiously stepping into a sunlit glade, or a red-tailed hawk soaring overhead—reminds visitors that they are guests in a realm where the wild still holds sway. In the heart of Whispering Pines lies a crystal-clear lake, its surface shimmering like a mirror under the midday sun. Here, the silence is punctuated only by the gentle lapping of water against the shore and the occasional call of a loon. Fish dart beneath the surface, their movements creating ripples that expand and fade into the tranquil stillness. Come evening, as the sky blushes with hues of pink and gold, a chorus of frogs and crickets serenades the fading light. The first stars emerge overhead, their twinkling reflections mirrored in the lake's glassy surface. Around a crackling fire, stories are shared beneath a canopy of stars, weaving a tapestry of memories that linger long after the embers have turned to ash. Whispering Pines is more than a place—it is a sanctuary for the weary, a haven for the restless soul seeking respite from the frenetic pace of modern life. Here, amidst the timeless beauty of nature, one finds a profound connection to the earth and a sense of peace that transcends words.");
}