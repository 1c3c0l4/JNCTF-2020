require 'openssl'
require 'base64'

def aes_encrypt(key,encrypted_string)
	aes = OpenSSL::Cipher.new("AES-128-ECB")
	aes.encrypt
	aes.key = key
	cipher = aes.update(encrypted_string) << aes.final
	return Base64.encode64(cipher)
end

print "Show me Your flag:"
flag = gets.chomp

key = "Welcome_To_JNCTF"
cipher = "q6gng2lEJA60aPtwtUSbSc4WAzUtTDIeXrXqaJCyfIQ=\n"

text = aes_encrypt(key,flag)

if cipher == text
	puts "you got it!"
else
	puts "try again!"
end