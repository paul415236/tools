" Chewei.Lin <chewei.lin@vivotek.com>

syntax on

" status
":set statusline=%4*%<\%m%<[%f\%r%h%w]\ [%{&ff},%{&fileencoding},%Y]%=\[Position=%l,%v,%p%%]
set laststatus=2            " set the bottom status bar

function! ModifiedColor()
    if &mod == 1
        hi statusline guibg=White ctermfg=8 guifg=OrangeRed4 ctermbg=15
    else
        hi statusline guibg=White ctermfg=8 guifg=DarkSlateGray ctermbg=15
    endif
endfunction

au InsertLeave,InsertEnter,BufWritePost   * call ModifiedColor()
" default the statusline when entering Vim
hi statusline guibg=White ctermfg=8 guifg=DarkSlateGray ctermbg=15

" Formats the statusline
set statusline=%f                           " file name
set statusline+=[%{strlen(&fenc)?&fenc:'none'}, "file encoding
set statusline+=%{&ff}] "file format
set statusline+=%y      "filetype
set statusline+=%h      "help file flag
set statusline+=[%{getbufvar(bufnr('%'),'&mod')?'modified':'saved'}]      
"modified flag

set statusline+=%r      "read only flag

set statusline+=\ %=                        " align left
set statusline+=Line:%l/%L[%p%%]            " line X of Y [percent of file]
set statusline+=\ Col:%c                    " current column
set statusline+=\ Buf:%n                    " Buffer number
set statusline+=\ [%b][0x%B]\               " ASCII and byte code under cursor


" scheme
colorscheme desert
"colorscheme torte

" mouse
nmap <F3> :set mouse=a<CR><CR>
nmap <F4> :set mouse=<CR><CR>

" window
nmap + <C-W>+
nmap - <C-W>-
nmap > <C-w>>
nmap < <C-w><

" tab
:set tabstop=4
:set shiftwidth=4
:set expandtab
nmap <F1> :set noexpandtab<CR><CR>
nmap <F2> :set expandtab<CR><CR>

" auto tab/space conversion
autocmd FileType make setlocal shiftwidth=4 tabstop=4 softtabstop=4 noexpandtab
autocmd FileType html setlocal shiftwidth=4 tabstop=4 softtabstop=4 noexpandtab
autocmd FileType xml setlocal shiftwidth=4 tabstop=4 softtabstop=4 noexpandtab
autocmd FileType htmldjango setlocal shiftwidth=4 tabstop=4 softtabstop=4 noexpandtab
autocmd FileType javascript setlocal shiftwidth=4 tabstop=4 softtabstop=4 noexpandtab
autocmd BufNewFile,BufRead *.html,*.htm,*.css,*.js,*.sh,*.mk,*.xml,*.config,*conf set noexpandtab

" tag
:set tags=./tags,./TAGS,tags;~,TAGS;~

function! UpdateCtags()
	let curdir=getcwd()
	while !filereadable("./tags")
		cd ..
		if getcwd() == "/"
			break
		endif
	endwhile
	if filewritable("./tags")
		!ctags -R --file-scope=yes --langmap=c:+.h --languages=c,c++ --links=yes --c-kinds=+p --c++-kinds=+p --fields=+iaS --extra=+q
		TlistUpdate
	endif
	execute ":cd " . curdir
endfunction

" taglist
nmap <F8> :TlistToggle<CR><CR>
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
set ut=10

"nmap <F10> :call UpdateCtags()<CR>
"autocmd BufWritePost *.c,*.h,*.cpp call UpdateCtags()

