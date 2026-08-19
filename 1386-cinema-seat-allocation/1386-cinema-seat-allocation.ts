function maxNumberOfFamilies(n: number, reservedSeats: number[][]): number {
    const rows = new Map<number, number>();

    for (const [row, seat] of reservedSeats) {
        if (seat >= 2 && seat <= 9) {
            rows.set(row, (rows.get(row) ?? 0) | (1 << seat));
        }
    }

    let result = (n - rows.size) * 2;

    for (const mask of rows.values()) {
        const left = (mask & ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5))) === 0;
        const middle = (mask & ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))) === 0;
        const right = (mask & ((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9))) === 0;

        if (left && right) {
            result += 2;
        } else if (left || middle || right) {
            result += 1;
        }
    }

    return result;
}