#!/usr/bin/env/ bash
WM=$HOME/projects/EOS/2_shell/bin/watermark.png
SCALE = 50

echo -e "This will overwrite all of the images in this directory."\\n"Are you sure want to continue? {Y/n}"
read REPLY

if
	[ "$REPLY" != "n" ] && [ "$REPLY" != "N" ]
then
	file -i * | grep image | awk -F':' '{ print $1 }' | while read IMAGE
		do
			echo Watermarking $IMAGE
			composite --dissolve 40% -gravity center -quality 100 \( $WM -resize $SCALE% \) "$IMAGE" "$IMAGE"
		done
	else
		echo exiting
		exit 0
fi

exit 0

	
