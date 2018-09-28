declare module dcrypto {
    /**
     * Encrypt a string
     * @param {string} text text to encrypt
     * @param {number} seed crypto seed, 0 - 255
     * @param {string} [e] two letters used in crypto, default is 'ab'
     */
    export function encrypt(text: string, seed: number, e?: string): string
    /**
     * Decrypt a string
     * @param {string} text text to decrypt
     * @param {number} seed crypto seed, 0 - 255
     * @param {string} [e] two letters used in crypto, default is 'ab'
     */
    export function decrypt(text: string, seed: number, e?: string): string
}

export = dcrypto
