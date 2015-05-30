#ifndef ROW_DISPLAY_H_
#define ROW_DISPLAY_H_

#include "Arduino.h"
#include "SPI.h"

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

/*
 * Display controls multiple 8x8-LED-Matrix elements connected together to a single row.
 * For example ten pieces of 8x8-Matrix will result in display consisting of 80x8 LEDs (8 lines, each 80 pixels).
 * Each 8x8-Matrix is controlled by MAX7291 connected trough SPI and it requires separate
 * Slave Select line.
 * We are using hardware controlled SPI, depending on Arduino version it occupies different pins. On Mega
 * MOSI is on 51 and SCK on 52. Plus extra SS pin for each MAX7291.
 *
 * Each font has 8x8 pixels and can be displayed on single 8x8-Matrix.
 */
class RowDisplay {
public:
	/**
	 * #ssSize defines amount of Slave Select lines and implicitly the amount of MAX7291 chips to be controlled.
	 *
	 * Vararg parameter gives list of Slave Select lines in order of the occurrence of 8x8-Matrix elements within a row.
	 */
	RowDisplay(uint8_t ssSize, ...);

	/** Initialized SPI and 8x8-Matrix elements. */
	void setup();

	/** Shows provided character on 8x8-Matrix given by #ss (Slave Select line). */
	void showAt(uint8_t fontCode, uint8_t ss);

	/**
	 * Shows text on a few 8x8-Matrix elements. Each character will be displayed on separate 8x8-Matrix.
	 * Text length has to match amount of 8x8-Matrix elements determined by #ssSize, otherwise it will be trimmed.
	 *
	 * Vararg parameter gives list of Slave Select lines in order of the occurrence of 8x8-Matrix elements within a row.
	 *
	 * The size of #text and #vararg list is given by #ssSize.
	 */
	void show(uint8_t* text, uint8_t ssSize, ...);

	/**
	 * Replaces current text with new one. Both should have the same length.
	 * Function automatically determines characters that has changed
	 * and substitutes only those by playing animation in given direction.
	 */
	void replace(uint8_t* text, Direction direction, uint8_t ssSize, ...);

	/**
	 * Plays animation on given 8x8-Matrix determined by #ss.
	 *
	 * Animation is transparent, so it will not cover current content.
	 *
	 * Animation consists of few frames given by #frames. Vararg contains a list of pointers to 8x8 fonts, where
	 * each font gives simple frame for the animation. Size of the list is equal to #frames.
	 */
	void animateAt(uint8_t ss, uint8_t frames, ...);

	/**
	 * Scrolls given text in given direction over few 8x8-Matrix elements.
	 * The amount is given by #ssSize and SS lines as vararg.
	 */
	void scroll(uint8_t* text, Direction direction, uint8_t ssSize, ...);

private:
	/* Array containing Slave Select lines, starting form left to right */
	uint8_t* ss;

	/* Amount of SS lines.*/
	uint8_t ssSize;

	void setupMax(uint8_t ss);
	void send(uint8_t ss, uint8_t address, uint8_t value);
	void clear(uint8_t ss);
};

#endif /* ROW_DISPLAY_H_ */
