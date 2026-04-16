#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class AES_Crypto {
public:

	enum Mode {
		CBC,
		ECB,
		GCM
	};

	AES_Crypto(Mode mode = CBC) : mode_(mode) {

	}

	~AES_Crypto() {

		uninit();
	}


	static std::vector<unsigned char> generate_key(size_t length = 32) {
		std::vector<unsigned char> key(length);
		if (RAND_bytes(key.data(), length) != 1) {
			throw std::runtime_error("Failed to generate random key");
		}
		return key;
	}

	static std::vector<unsigned char> generate_iv(size_t length = 16) {
		std::vector<unsigned char> iv(length);
		if (RAND_bytes(iv.data(), length) != 1) {
			throw std::runtime_error("Failed to generate random IV");
		}
		return iv;
	}

	bool init(const std::vector<unsigned char>& key,
		const std::vector<unsigned char>& iv) {

		m_key.assign(key.begin(), key.end());
		m_iv.assign(iv.begin(), iv.end());

		ctx_ = EVP_CIPHER_CTX_new();
		if (!ctx_) {
			ctx_ = nullptr;
			throw std::runtime_error("Failed to create cipher context");
		}

		/*
		try {

			const EVP_CIPHER* cipher = get_cipher(key.size());
			if (!cipher) {
				throw std::runtime_error("Unsupported key size");
			}

			if (EVP_DecryptInit_ex(ctx_, cipher, nullptr, key.data(), iv.data()) != 1) {
				throw std::runtime_error("DecryptInit failed");
			}


			EVP_CIPHER_CTX_set_padding(ctx_, 1);
		}
		catch (...) {
			EVP_CIPHER_CTX_free(ctx_);
			throw;
		}
		*/

		return true;

	}

	void uninit() {
		if (ctx_) {
			EVP_CIPHER_CTX_free(ctx_);
			ctx_ = nullptr;
		}
	}


	std::vector<unsigned char> encrypt(const std::vector<unsigned char>& plaintext) {


		try {

			if (ctx_ == nullptr) {
				throw std::runtime_error("encrypt ctx_=nullptr failed");
			}

			const EVP_CIPHER* cipher = get_cipher(m_key.size());
			if (!cipher) {
				throw std::runtime_error("Unsupported key size");
			}

			if (EVP_EncryptInit_ex(ctx_, cipher, nullptr, m_key.data(), m_iv.data()) != 1) {
				throw std::runtime_error("EncryptInit failed");
			}

			EVP_CIPHER_CTX_set_padding(ctx_, 1);
			

			std::vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
			int len;
			int ciphertext_len = 0;

			if (EVP_EncryptUpdate(ctx_, ciphertext.data(), &len, plaintext.data(), plaintext.size()) != 1) {
				throw std::runtime_error("EncryptUpdate failed");
			}
			ciphertext_len = len;

			if (EVP_EncryptFinal_ex(ctx_, ciphertext.data() + len, &len) != 1) {
				throw std::runtime_error("EncryptFinal failed");
			}
			ciphertext_len += len;
			EVP_CIPHER_CTX_reset(ctx_);

			ciphertext.resize(ciphertext_len);
			return ciphertext;

		}
		catch (...) {
			throw;
		}
	}




	std::vector<unsigned char> decrypt(const std::vector<unsigned char>& ciphertext) {


		try {

			if (ctx_ == nullptr) {
				throw std::runtime_error("decrypt ctx_=nullptr failed");
			}
			const EVP_CIPHER* cipher = get_cipher(m_key.size());
			if (!cipher) {
				throw std::runtime_error("Unsupported key size");
			}

			if (EVP_DecryptInit_ex(ctx_, cipher, nullptr, m_key.data(), m_iv.data()) != 1) {
				throw std::runtime_error("DecryptInit failed");
			}


			EVP_CIPHER_CTX_set_padding(ctx_, 1);


			std::vector<unsigned char> plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);
			int len;
			int plaintext_len = 0;

			if (EVP_DecryptUpdate(ctx_, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
				throw std::runtime_error("DecryptUpdate failed");
			}
			plaintext_len = len;

			if (EVP_DecryptFinal_ex(ctx_, plaintext.data() + len, &len) != 1) {

				unsigned long err = ERR_get_error();
				char err_buf[512];
				ERR_error_string_n(err, err_buf, sizeof(err_buf));
				std::string errInfo("DecryptFinal failed:");
				errInfo.append(err_buf);

				throw std::runtime_error(errInfo.c_str());
			}
			plaintext_len += len;

			EVP_CIPHER_CTX_reset(ctx_);

			plaintext.resize(plaintext_len);
			return plaintext;

		}
		catch (...) {
			throw;
		}
	}

private:
	Mode mode_;

	EVP_CIPHER_CTX* ctx_ = nullptr;

	std::vector<unsigned char> m_key;
	std::vector<unsigned char> m_iv;

	const EVP_CIPHER* get_cipher(size_t key_length) {
		switch (key_length) {
		case 16: return EVP_aes_128_cbc();  // 128-bit key
		case 24: return EVP_aes_192_cbc();  // 192-bit key
		case 32: return EVP_aes_256_cbc();  // 256-bit key
		default: return nullptr;
		}
	}
};