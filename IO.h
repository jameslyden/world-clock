/* WorldClock: a multiple time-zone clock for a 16x2 display
 * Copyright 2015, James Lyden <james@lyden.org>
 * This code is licensed under the terms of the GNU General Public License.
 * See COPYING, or refer to http://www.gnu.org/licenses, for further details.
 *
 * This file contains the mapping of logical I/O channels to physical pin numbers.
 */

// LCD outputs (and inputs, which must be mapped to unused pins)
#define LCD0_OUT	7
#define LCD1_OUT	8
#define LCD0_IN	6
#define LCD1_IN	9

// input indices
#define UP		0
#define DN		1
#define DOWN	1
#define LT		2
#define LEFT	2
#define RT		3
#define RIGHT	3
#define OK		4

// input button pin numbers
const int BUTTON[] = {
	10,	// up
	11,	// down
	12,	// left
	13,	// right
	2 };	// ok

// masks for input values
const int PRESS[] = {
	0b00001,		// up
	0b00010,		// down
	0b00100,		// left
	0b01000,		// right
	0b10000};	// ok

